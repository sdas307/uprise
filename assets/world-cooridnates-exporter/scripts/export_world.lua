------------------------------------------------------------
-- Parse Layer Export Configurations
------------------------------------------------------------

local function parseLayerData(data)

    local config = {}

    for key, value in data:gmatch("(%w+)%s*=%s*([^;]+)") do
        config[key] = value:match("^%s*(.-)%s*$")
    end

    return config

end

------------------------------------------------------------
-- Find opaque pixel bounds
------------------------------------------------------------
local function getOpaqueBounds(image)

    local minX = image.width
    local minY = image.height

    local maxX = -1
    local maxY = -1

    for y = 0, image.height - 1 do
        for x = 0, image.width - 1 do

            local pixel = image:getPixel(x, y)
            local alpha = app.pixelColor.rgbaA(pixel)

            if alpha > 0 then

                if x < minX then
                    minX = x
                end

                if y < minY then
                    minY = y
                end

                if x > maxX then
                    maxX = x
                end

                if y > maxY then
                    maxY = y
                end

            end
        end
    end

    --------------------------------------------------------
    -- Image contains no opaque pixels
    --------------------------------------------------------

    if maxX < minX or maxY < minY then
        return nil
    end

    return {
        x = minX,
        y = minY,
        width = maxX - minX + 1,
        height = maxY - minY + 1
    }

end

------------------------------------------------------------
-- Check whether a tile contains any opaque pixels
------------------------------------------------------------

local function tileOccupied(image, startX, startY, tileSize)

    for y = startY, math.min(startY + tileSize - 1, image.height - 1) do

        for x = startX, math.min(startX + tileSize - 1, image.width - 1) do

            local pixel = image:getPixel(x, y)

            if app.pixelColor.rgbaA(pixel) > 0 then
                return true
            end

        end

    end

    return false

end

------------------------------------------------------------
-- Collect merged collider rectangles
------------------------------------------------------------

local function collectColliderRuns(cel)

    local TILE_SIZE = 16

    local image = cel.image

    local rectangles = {}

    --------------------------------------------------------
    -- Number of tiles
    --------------------------------------------------------

    local columns = math.ceil(image.width / TILE_SIZE)

    local rows = math.ceil(image.height / TILE_SIZE)

    --------------------------------------------------------
    -- Build occupancy grid
    --------------------------------------------------------

    local occupied = {}
    local visited = {}

    for row = 0, rows - 1 do

        occupied[row] = {}
        visited[row] = {}

        for column = 0, columns - 1 do

            occupied[row][column] = tileOccupied(image, column * TILE_SIZE, row * TILE_SIZE, TILE_SIZE)

            visited[row][column] = false

        end

    end

        for row = 0, rows - 1 do

        for column = 0, columns - 1 do

            if visited[row][column] then
                goto continue
            end

            if not occupied[row][column] then
                goto continue
            end

            --------------------------------------------
            -- Determine width
            --------------------------------------------

            local width = 1

            while
                column + width < columns and
                occupied[row][column + width] and
                not visited[row][column + width]
            do
                width = width + 1
            end

            --------------------------------------------
            -- Determine height
            --------------------------------------------

            local height = 1

            while row + height < rows do

                local valid = true

                for x = column, column + width - 1 do

                    if
                        not occupied[row + height][x]
                        or visited[row + height][x]
                    then

                        valid = false
                        break

                    end

                end

                if not valid then
                    break
                end

                height = height + 1

            end

            --------------------------------------------
            -- Mark visited
            --------------------------------------------

            for y = row, row + height - 1 do

                for x = column, column + width - 1 do

                    visited[y][x] = true

                end

            end

            --------------------------------------------
            -- Export rectangle
            --------------------------------------------

            table.insert(
                rectangles,
                {
                    x = cel.position.x + column * TILE_SIZE,
                    y = cel.position.y + row * TILE_SIZE,
                    width = width * TILE_SIZE,
                    height = height * TILE_SIZE
                }
            )

            ::continue::

        end

    end

    return rectangles

end

------------------------------------------------------------
-- Collect occupied tile positions
------------------------------------------------------------

local function collectTilePositions(cel)

    local TILE_SIZE = 16

    local image = cel.image

    local positions = {}

    --------------------------------------------------------
    -- Number of tiles
    --------------------------------------------------------

    local columns = math.ceil(image.width / TILE_SIZE)

    local rows = math.ceil(image.height / TILE_SIZE)

    --------------------------------------------------------
    -- Export occupied tiles
    --------------------------------------------------------

    for row = 0, rows - 1 do

        for column = 0, columns - 1 do

            if tileOccupied(
                image,
                column * TILE_SIZE,
                row * TILE_SIZE,
                TILE_SIZE
            ) then

                local worldX = cel.position.x + column * TILE_SIZE
                local worldY = cel.position.y + row * TILE_SIZE

                table.insert(
                    positions,
                    {
                        x = worldX - (worldX % TILE_SIZE),
                        y = worldY - (worldY % TILE_SIZE)
                    }
                )

            end

        end

    end

    return positions

end

------------------------------------------------------------
-- Collect tilemap tile positions and tile indices
------------------------------------------------------------

local function collectTilemapTiles(layer)

    local tiles = {}

    local cel = layer:cel(1)

    if not cel then
        return tiles
    end

    local image = cel.image

    --------------------------------------------------------
    -- Tile size comes from the layer's tileset
    --------------------------------------------------------

    local tileset = layer.tileset

    if not tileset then
        return tiles
    end

    local tileSize = tileset.grid.tileSize

    local tileWidth = math.abs(tileSize.width)
    local tileHeight = math.abs(tileSize.height)

    --------------------------------------------------------
    -- Read tilemap cells
    --------------------------------------------------------

    for pixel in image:pixels() do

        local tileIndex = app.pixelColor.tileI(pixel())

        ----------------------------------------------------
        -- Tile index 0 is the empty tile
        ----------------------------------------------------

        if tileIndex ~= 0 then

            table.insert(
                tiles,
                {
                    x = cel.position.x + pixel.x * tileWidth,
                    y = cel.position.y + pixel.y * tileHeight,
                    index = tileIndex
                }
            )

        end

    end

    return tiles

end

------------------------------------------------------------
-- Validate C identifier
------------------------------------------------------------

local function isValidIdentifier(name)

    if not name then
        return false
    end

    if name == "" then
        return false
    end

    return name:match("^[%a_][%w_]*$") ~= nil

end

------------------------------------------------------------
-- Collect exportable layers
------------------------------------------------------------

local function collectLayers(sprite)

    local groups = {}
    local exportedObjects = 0
    local invalidLayers = {}

    for _, layer in ipairs(sprite.layers) do

        ----------------------------------------------------
        -- Layer User Data contains the export group
        ----------------------------------------------------

        local layerData = parseLayerData(layer.data or "")

        local arrayName = layerData.name or ""
        local exportType = layerData.type or ""

        ----------------------------------------------------
        -- Empty User Data means ignore the layer
        ----------------------------------------------------

        if arrayName ~= "" then

            ------------------------------------------------
            -- Validate export group
            ------------------------------------------------

            if not isValidIdentifier(arrayName) then

                table.insert(invalidLayers, {
                    layer = layer.name,
                    group = arrayName
                })

            elseif exportType ~= "single"
                and exportType ~= "tile_positions"
                and exportType ~= "colliders"
                and exportType ~= "tilemap" then

                table.insert(invalidLayers, {
                    layer = layer.name,
                    group = arrayName
                })

            else

                --------------------------------------------
                -- Get cel from frame 1
                --------------------------------------------

                local cel = layer:cel(1)

                if cel then

                    ------------------------------------------------
                    -- Create export group if necessary
                    ------------------------------------------------

                    if not groups[arrayName] then
                        groups[arrayName] = {}
                    end

                    ------------------------------------------------
                    -- Choose export behaviour
                    ------------------------------------------------
                    if exportType == "tilemap" then

                        local tiles = collectTilemapTiles(layer)

                        for _, tile in ipairs(tiles) do

                            table.insert(
                                groups[arrayName],
                                tile
                            )

                            exportedObjects = exportedObjects + 1

                        end

                    elseif exportType == "colliders" then
                        
                        local rectangles = collectColliderRuns(cel)

                        for _, rectangle in ipairs(rectangles) do

                            table.insert(
                                groups[arrayName],
                                rectangle
                            )

                            exportedObjects = exportedObjects + 1

                        end

                    elseif exportType == "tile_positions" then

                        local positions = collectTilePositions(cel)

                        for _, position in ipairs(positions) do

                            table.insert(
                                groups[arrayName],
                                position
                            )

                            exportedObjects = exportedObjects + 1

                        end

                    elseif exportType == "single" then

                        local bounds = getOpaqueBounds(cel.image)

                        if bounds then

                            table.insert(
                                groups[arrayName],
                                {
                                    x = cel.position.x + bounds.x,
                                    y = cel.position.y + bounds.y
                                }
                            )

                            exportedObjects = exportedObjects + 1
                        
                        end

                    end
                end
            end
        end
    end

    return groups, exportedObjects, invalidLayers

end

------------------------------------------------------------
-- Get sorted export group names
------------------------------------------------------------

local function getSortedGroupNames(groups)

    local names = {}

    for name, _ in pairs(groups) do
        table.insert(names, name)
    end

    table.sort(names)

    return names

end

------------------------------------------------------------
-- Show invalid export groups
------------------------------------------------------------

local function showInvalidLayersDialog(invalidLayers)

    local dialog = Dialog {
        title = "Invalid Export Groups"
    }

    dialog:label{
        text = "Some layers contain invalid export groups."
    }

    dialog:separator()

    --------------------------------------------------------
    -- Limit displayed errors
    --------------------------------------------------------

    local displayLimit = 10

    local displayCount = math.min(#invalidLayers, displayLimit)

    for i = 1, displayCount do

        local item = invalidLayers[i]

        dialog:label{
            text = item.layer .. " -> " .. item.group
        }

    end

    --------------------------------------------------------
    -- Show remaining error count
    --------------------------------------------------------

    if #invalidLayers > displayLimit then

        dialog:label{
            text = "... and " .. (#invalidLayers - displayLimit) .. " more."
        }

    end

    dialog:separator()

    dialog:label{
        text = "Export groups must be valid C identifiers."
    }

    dialog:button{
        text = "OK",
        focus = true
    }

    dialog:show()

end

------------------------------------------------------------
-- Write C export
------------------------------------------------------------

local function writeExport(path, groups)

    local file = io.open(path, "w")

    if not file then
        return false
    end

    --------------------------------------------------------
    -- File header
    --------------------------------------------------------

    file:write("//==========================================================\n")

    file:write("// Generated by World Coordinates Exporter\n")

    file:write("//==========================================================\n\n")

    --------------------------------------------------------
    -- Sort groups for deterministic output
    --------------------------------------------------------

    local groupNames = getSortedGroupNames(groups)

    --------------------------------------------------------
    -- Write groups
    --------------------------------------------------------

    for _, name in ipairs(groupNames) do

        local objects = groups[name]

        --------------------------------------------------------
        -- Tilemap export
        --------------------------------------------------------

        if #objects > 0 and objects[1].index then

            file:write("static const TileObject " .. name .. "[] =\n")

            file:write("{\n")

            for _, object in ipairs(objects) do

                file:write(
                    string.format(
                        "    { %d, %d, %d },\n",
                        object.x,
                        object.y,
                        object.index
                    )
                )

            end

            file:write("};\n\n")

        --------------------------------------------------------
        -- Rectangle export
        --------------------------------------------------------

        elseif #objects > 0 and objects[1].width then

            file:write("static const Rectangle " .. name .. "[] =\n")

            file:write("{\n")

            for _, object in ipairs(objects) do

                file:write(string.format("    { %d, %d, %d, %d },\n", object.x, object.y, object.width, object.height))

            end

            file:write("};\n\n")

            --------------------------------------------------------
            -- Vector2 export (existing behaviour)
            --------------------------------------------------------

        else

            file:write("static const Vector2 " .. name .. "[] =\n")

            file:write("{\n")

            for _, object in ipairs(objects) do

                file:write(string.format("    { %d, %d },\n", object.x, object.y))

            end

            file:write("};\n\n")

        end

    end

    file:close()

    return true

end

------------------------------------------------------------
-- Export World Coordinates
------------------------------------------------------------

function exportWorldCoordinates(plugin)

    local sprite = app.activeSprite

    --------------------------------------------------------
    -- Validate active sprite
    --------------------------------------------------------

    if not sprite then

        app.alert("No sprite is open.")

        return
    end

    --------------------------------------------------------
    -- Collect world objects
    --------------------------------------------------------

    local groups, exportedObjects, invalidLayers = collectLayers(sprite)

    --------------------------------------------------------
    -- Check invalid export groups
    --------------------------------------------------------

    if #invalidLayers > 0 then

        showInvalidLayersDialog(invalidLayers)

        return
    end

    --------------------------------------------------------
    -- Check empty export
    --------------------------------------------------------

    if exportedObjects == 0 then

        app.alert("No exportable layers found.\n\n" .. "Use Configure Layer to assign " .. "an export group.")

        return
    end

    --------------------------------------------------------
    -- Output path
    --------------------------------------------------------

    local path = app.fs.joinPath(app.fs.userDocsPath, "world_coordinates.txt")

    --------------------------------------------------------
    -- Write export
    --------------------------------------------------------

    if not writeExport(path, groups) then

        app.alert("Couldn't create output file:\n\n" .. path)

        return
    end

    --------------------------------------------------------
    -- Success
    --------------------------------------------------------

    app.alert("Export complete!\n\n" .. "Objects exported: " .. exportedObjects .. "\n\n" .. "Output:\n" .. path)

end