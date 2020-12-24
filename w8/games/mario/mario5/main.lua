Class = require 'class'
push = require 'push'

require 'Map'

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

WINDOW_HEIGHT = 720
WINDOW_WIDTH = 1280

math.randomseed(os.time())

love.graphics.setDefaultFilter('nearest', 'nearest')

map = Map()

function love.load()
    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        resizeable = true,
        vsync = true
    })
end

function love.resize(w, h)
    push:resize(w, h)
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    end
end

function love.update(dt)
    map:update(dt)
end

function love.draw()
    push:apply('start')

    love.graphics.clear(108/255, 140/255, 255/255, 255/255)
    
    love.graphics.translate(math.floor(-map.camX + 0.5), math.floor(-map.camY + 0.5))
    map:render()
    
    push:apply('end')
end