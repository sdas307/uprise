------------------------------------------------------------
-- World Coordinate Exporter
------------------------------------------------------------

local pluginInstance = nil

------------------------------------------------------------
-- Load plugin scripts
------------------------------------------------------------

local function loadScript(path)

    local pluginPath = pluginInstance.path

    dofile(
        app.fs.joinPath(
            pluginPath,
            path
        )
    )
end

------------------------------------------------------------
-- Plugin initialization
------------------------------------------------------------

function init(plugin)

    pluginInstance = plugin

    loadScript("scripts/configure_layer.lua")
    loadScript("scripts/export_world.lua")

    plugin:newCommand
    {
        id = "WorldCoordinateExporterConfigureLayer",
        title = "Configure Layer",
        group = "layer_popup",
        onclick = function()
            configureExportLayer()
        end
    }

    plugin:newCommand
    {
        id = "WorldCoordinateExporterExport",
        title = "Export World Coordinates",
        group = "file_export",
        onclick = function()
            exportWorldCoordinates(plugin)
        end
    }

end

------------------------------------------------------------
-- Plugin shutdown
------------------------------------------------------------

function exit(plugin)

end