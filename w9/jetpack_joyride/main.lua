Class = require 'class'
push = require 'push'

require 'Animation'
require 'Map'
require 'Player'

-- close resolution to NES but 16:9
VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

-- actual window resolution
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

-- seed RNG
math.randomseed(os.time())

-- makes upscaling look pixel-y instead of blurry
love.graphics.setDefaultFilter('nearest', 'nearest')
 
-- an object to contain our map data
map = Map()

-- performs initialization of all objects and data needed by program
function love.load()

    -- sets up a different, better-looking retro font as our default
    bigHelsinkiFont = love.graphics.newFont('fonts/helsinki.ttf', 24)
    love.graphics.setFont(bigHelsinkiFont)

    helsinkiFont = love.graphics.newFont('fonts/helsinki.ttf', 8)
    love.graphics.setFont(helsinkiFont)
    
    retroFont = love.graphics.newFont('fonts/font.ttf', 8)
    love.graphics.setFont(retroFont)

    -- sets up virtual screen resolution for an authentic retro feel
    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        resizable = true
    })

    love.window.setTitle('Jetpack Joyride')

    love.keyboard.keysPressed = {}
    love.keyboard.keysReleased = {}

    gameState = 'start'
end

-- called whenever window is resized
function love.resize(w, h)
    push:resize(w, h)
end

-- global key pressed function
function love.keyboard.wasPressed(key)
    if (love.keyboard.keysPressed[key]) then
        return true
    else
        return false
    end
end

-- global key released function
function love.keyboard.wasReleased(key)
    if (love.keyboard.keysReleased[key]) then
        return true
    else
        return false
    end
end

-- called whenever a key is pressed
function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    elseif key == 'enter' or key == 'return' then
        if gameState == 'start' then
            gameState = 'play'
        end
    end

    love.keyboard.keysPressed[key] = true
end

-- called whenever a key is released
function love.keyreleased(key)
    love.keyboard.keysReleased[key] = true
end

-- called every frame, with dt passed in as delta in time since last frame
function love.update(dt)
    if gameState == 'play' then
        map:update(dt)
        -- reset all keys pressed and released this frame
        love.keyboard.keysPressed = {}
        love.keyboard.keysReleased = {}
    end
end

-- called each frame, used to render to the screen
function love.draw()
    -- begin virtual resolution drawing
    push:apply('start')

    if gameState == 'start' then
        love.graphics.setFont(bigHelsinkiFont)
        love.graphics.printf('JETPACK JOYRIDE', 0, VIRTUAL_HEIGHT / 3, VIRTUAL_WIDTH, 'center')

        love.graphics.setFont(helsinkiFont)
        love.graphics.printf('by Abelard Bautista', 0, VIRTUAL_HEIGHT / 2.25, VIRTUAL_WIDTH, 'center')

        love.graphics.setFont(retroFont)
        love.graphics.printf('OH NO! YOU ARE LOST IN SPACE AND HAVE HIT AN ASTEROID FIELD!\n\n<Press [SPACE] to use your jetpack to escape>\nPress [Enter] to begin', 0, VIRTUAL_HEIGHT / 1.75, VIRTUAL_WIDTH, 'center')
    elseif gameState == 'play' then
        -- clear screen using Mario background blue
        love.graphics.clear(22/255, 7/255, 71/255, 255/255)

        -- renders our map object onto the screen
        love.graphics.translate(math.floor(-map.camX + 0.5), math.floor(-map.camY + 0.5))
        map:render()
    end

    

    -- end virtual resolution
    push:apply('end')
end
