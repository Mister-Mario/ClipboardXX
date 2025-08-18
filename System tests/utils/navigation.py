import sys
#Needs to be edited for each system
sikuli_jar_path = "C:\\Users\\mario\\Desktop\\Uni\\TFG\\Advanced-Clipboard\\System tests\\sikulixide-2.0.5.jar"

if sikuli_jar_path not in sys.path:
    sys.path.append(sikuli_jar_path)

from sikuli import *
from utils import create_img

def go_to_main_window():
    click(create_img("ShortcutsView\\ExpandButton.png"))
    wait(0.25)
    wait(create_img("MainView\\MainView.png"))