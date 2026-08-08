------------------------------------------------------------
-- Configure Export Layer
------------------------------------------------------------

function configureExportLayer()

    local sprite = app.activeSprite
    local layer = app.activeLayer

    --------------------------------------------------------
    -- Validate active sprite
    --------------------------------------------------------

    if not sprite then

        app.alert("No sprite is open.")

        return
    end

    --------------------------------------------------------
    -- Validate active layer
    --------------------------------------------------------

    if not layer then

        app.alert("No layer is selected.")

        return
    end

    --------------------------------------------------------
    -- Current export group
    --------------------------------------------------------

    local currentGroup = layer.data or ""

    --------------------------------------------------------
    -- Dialog
    --------------------------------------------------------

    local dialog = Dialog
    {
        title = "Configure Export Layer"
    }

    dialog:label
    {
        label = "Layer:",
        text = layer.name
    }

    dialog:entry
    {
        id = "groupName",
        label = "Export Group:",
        text = currentGroup
    }

    dialog:separator()

    dialog:button
    {
        id = "save",
        text = "Save",
        focus = true,
        onclick = function()

            local groupName = dialog.data.groupName

            ------------------------------------------------
            -- Empty group disables export
            ------------------------------------------------

            if groupName == "" then

                layer.data = ""

                dialog:close()

                app.alert(
                    "Export disabled for layer:\n\n" ..
                    layer.name
                )

                return
            end

            ------------------------------------------------
            -- Validate identifier
            ------------------------------------------------

            if not groupName:match(
                "^[%a_][%w_]*$"
            ) then

                app.alert(
                    "Invalid export group.\n\n" ..
                    "Export groups must be valid " ..
                    "C identifiers."
                )

                return
            end

            ------------------------------------------------
            -- Save
            ------------------------------------------------

            layer.data = groupName

            dialog:close()

        end
    }

    dialog:button
    {
        text = "Cancel"
    }

    dialog:show
    {
        wait = false
    }

end