event = {}

function event.register(eventName, callback)
	if(event[eventName] == nil) then
		event[eventName] = {}
		event[eventName].callbacks = {}
	end

	table.insert(event[eventName].callbacks, callback)
end

function event.trigger(eventName, ...)
	if(event[eventName]) then
		for i, cb in pairs(event[eventName].callbacks) do
			if type(cb) == "function" then
				cb(...)
			elseif cb.onEvent then
				cb:onEvent(eventName, ...)
			end
		end
	end
end

function event.delete(eventName, callback)
	if(event[eventName]) then
		for i, cb in pairs(event[eventName].callbacks) do
			if(callback == cb) then
				table.remove(event[eventName].callbacks, i)
			end
		end
	end
end