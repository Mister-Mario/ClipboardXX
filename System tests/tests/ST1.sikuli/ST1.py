import sys
import os

script_path = getBundlePath()

parent_path = os.path.abspath(os.path.join(script_path, "..\\.."))

if parent_path not in sys.path:
    sys.path.append(parent_path)

from utils import utils, navigation
try:
    utils.set_up()
    navigation.go_to_main_window_from_shortcuts()
    #Load to memory cell 1 Hello
    click(utils.create_img("MainView\\MemoryCell1.png"))
    wait(0.25)
    type(utils.create_img("MainView\\MemoryCellInput.png"), "Hello")
    wait(0.25)
    click(utils.create_img("MainView\\LoadCell.png"))
    wait(0.25)
    wait(utils.create_img("ExpectedMemoryCell1.png"))
    #Load it to the clipboard
    click(utils.create_img("MainView\\LoadClipboard.png"))
    click(utils.create_img("MainView\\ClipboardCell.png"))
    wait(utils.create_img("ExpectedClipboard-1.png"))
    #Clear the clipboard
    click(utils.create_img("MainView\\ClearCell.png"))
    wait(utils.create_img("ExpectedClipboard-2.png"))
    

except Exception:
    print("Test Failed, capturing actual screen")
    ruta_captura = capture(SCREEN)
    print("Path of screen capture", ruta_captura)

finally:
    utils.tear_down()