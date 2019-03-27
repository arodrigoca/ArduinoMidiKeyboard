#export DBUS_SESSION_BUS_ADDRESS=unix:path=/run/dbus/system_bus_socket
if [ ! -f /tmp/started.txt ]; then
	touch "/tmp/started.txt"
	echo "System just started now!"
	python3 shutdown_button.py &
	python3 button_start_interrupt.py
else
	echo "A session is already running. Not Loading Bash profile script"
fi
