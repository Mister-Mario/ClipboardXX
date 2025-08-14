import sys
import os

script_path = getBundlePath()

parent_path = os.path.abspath(os.path.join(script_path, "..\\.."))

if parent_path not in sys.path:
    sys.path.append(parent_path)

from utils import *
try:
    utils.before_each()
    utils.open_clipboardXX()

except FindFailed:
    print "Test Failed, capturing actual screen"
    ruta_captura = capture(SCREEN)
    print "Path of screen capture", ruta_captura

finally:
    utils.after_each()
    
