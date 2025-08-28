import sys

from paths import *
sikuli_jar_path = get_sikulix_jar_path()
if sikuli_jar_path not in sys.path:
    sys.path.append(sikuli_jar_path)

from sikuli import *
from utils import create_img

def go_to_main_window_from_shortcuts():
    click(create_img("ShortcutsView\\ExpandButton.png"))
    wait(0.25)
    wait(create_img("MainView\\MainView.png"))

def go_to_export():
    click(create_img("MainView\\ExportButton.png"))
    wait(0.25)
    wait(create_img("Export&ImportView\\ExportView.png"))

def go_to_import():
    click(create_img("MainView\\ImportButton.png"))
    wait(0.25)
    wait(create_img("Export&ImportView\\ImportView.png"))

def go_back_to_main_window():
    click(create_img("MainView\\CancelButton.png"))
    wait(0.25)
    wait(create_img("MainView\\MainView.png"))

def bring_forward_tray_icon():
    click(create_img("External\\TrayIcon.png"))
    wait(0.25)
    rightClick(create_img("External\\Clipboard++TrayIcon.png"))
    wait(0.25) 
    click(create_img("External\\ShowTrayIcon.png"))
    wait(create_img("ShortcutsView\\ShortcutsView.png"))