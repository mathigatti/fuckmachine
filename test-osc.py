"""Small example OSC server

This program listens to several addresses, and prints some information about
received packets.
"""
import argparse

from pythonosc.dispatcher import Dispatcher
from pythonosc import osc_server

def print_toggle_handler(unused_addr, args, volume):
  try:
    print("{0}: {1}".format(args[0], volume))
  except ValueError: pass

def print_slider_handler(unused_addr, args, volume):
  print("{0}: {1}".format(args[0], round(volume,3)))


if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("--ip",
      default="0.0.0.0", help="The ip to listen on")
  parser.add_argument("--port",
      type=int, default=10000, help="The port to listen on")
  args = parser.parse_args()

  dispatcher = Dispatcher()
  dispatcher.map("/oscControl/toggle1", print_toggle_handler, "on/off")
  dispatcher.map("/oscControl/slider1", print_slider_handler, "Speed")

  server = osc_server.ThreadingOSCUDPServer(
      (args.ip, args.port), dispatcher)
  print("Serving on {}".format(server.server_address))
  server.serve_forever()