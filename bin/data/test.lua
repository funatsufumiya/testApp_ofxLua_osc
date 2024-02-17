function setup()
    -- print("setup")
end

function draw()
    -- of.background(0)
end

function oscReceived(message)
    -- local addr = message:getAddress()
    print("oscReceived", message)
end