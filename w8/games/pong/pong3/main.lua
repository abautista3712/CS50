WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

VIRTUAL_WIDTH = 432
VIRTUAL_HEIGHT = 243

push = require 'push'

function love.load()
    love.graphics.setDefaultFilter('nearest', 'nearest')

    smallFont = love.graphics.newFont('font.ttf', 8)
    
    scoreFont = love.graphics.newFont('font.ttf', 32)

    player1Score = 0
    player2Score = 0

    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        fullscreen = false,
        vsync = true,
        resizable = false
    })
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    end
end

function love.draw()
    push:apply('start')

    -- Render Background Color
    love.graphics.clear(40 / 255, 45 / 255, 52 / 255, 255 / 255)

    -- Render Ball (Center)
    love.graphics.rectangle('fill', VIRTUAL_WIDTH / 2 - 2, VIRTUAL_HEIGHT / 2 - 2, 5, 5)

    -- Render First Paddle (Left Side)
    love.graphics.rectangle('fill', 5, 20, 5, 20)

    -- Render Second Paddle (Right Side)
    love.graphics.rectangle('fill', VIRTUAL_WIDTH - 10, VIRTUAL_HEIGHT - 40, 5, 20)

    -- Render Welcome Message
    love.graphics.setFont(smallFont)
    love.graphics.printf('Hello Pong!', 0, 20, VIRTUAL_WIDTH, 'center')
    
    -- Render Score
    love.graphics.setFont(scoreFont)
    love.graphics.print(player1Score, VIRTUAL_WIDTH / 2 - 50, VIRTUAL_HEIGHT / 3)
    love.graphics.print(player2Score, VIRTUAL_WIDTH / 2 + 30, VIRTUAL_HEIGHT / 3)

    push:apply('end')
end