import sys
import os
#Needs to be edited for each system
shortcuts_path = "C:\\Users\\mario\\Desktop\\Clipboard++-1.0.1-win64\\assets\\conf"
app_exe_path = "C:\\Users\\mario\\Desktop\\Clipboard++-1.0.1-win64\\Clipboard++.exe - Acceso directo.lnk"
sikuli_jar_path = "C:\\Users\\mario\\Desktop\\Uni\\TFG\\Advanced-Clipboard\\System tests\\sikulixide-2.0.5.jar"

if sikuli_jar_path not in sys.path:
    sys.path.append(sikuli_jar_path)

from sikuli import *

app_name = "Clipboard++.exe" 
script_path = getBundlePath() #This path will be from inside the tests folder
test_files_path = script_path + "\\..\\..\\resources\\files"

def get_test_files_path():
    return test_files_path

def intialize_sikulix():
    images_path = script_path + "\\..\\..\\resources\\images" 
    addImagePath(images_path) #Add our own images location
    Settings.DefaultTimeout = 15 #Increase the default timeout

def create_img(imgPath):
    pattern = Pattern(imgPath)
    pattern.similar(0.85)
    return pattern

def open_clipboardXX():
    App.open(app_exe_path)
    wait(0.25)
    wait(create_img("ShortcutsView\\ShortcutsView.png"))

def close_clipboardXX():
    click(create_img("External\\TrayIcon.png"))
    wait(0.25)
    rightClick(create_img("External\\Clipboard++TrayIcon.png"))
    wait(0.25) 
    click(create_img("External\\CloseTrayIcon.png"))

def delete_file(my_file):
    if os.path.isfile(my_file):
        os.remove(my_file)

def restore_shortcuts():
    base_shortcuts = None
    user_shortcuts = None
    
    try:
        base_shortcuts = open(shortcuts_path + "\\shortCutsBase.csv", 'r', encoding='utf-8')
        user_shortcuts = open(shortcuts_path + "\\shortCuts.csv", 'w', encoding='utf-8')
        
        for linea in base_shortcuts:
            user_shortcuts.write(linea)
            
        print("Shortcuts restored")

    except Exception:
        print("Error while restoring shortcuts")

    finally:
        if base_shortcuts:
            base_shortcuts.close()
        if user_shortcuts:
            user_shortcuts.close()

def restore_blank():
    blank = None
    
    try:
        blank = open(test_files_path + "\\Blank.txt", 'w')#When opening with write we will empty the file
        
        print("Blank emptied restored")

    except Exception:
        print("Error while emptying")

    finally:
        if blank:
            blank.close()

def restore_existent_files():
    restore_shortcuts()
    restore_blank()

def delete_new_files():
    delete_file(test_files_path + "\\ST3_1_export.txt")
    delete_file(test_files_path + "\\ST3_2_export.txt")
    delete_file(test_files_path + "\\ST4_export.tx")
    delete_file(test_files_path + "\\ST5_export.tx")
    delete_file(test_files_path + "\\ST6_export.tx")

def set_up():
    print("Starting test")
    intialize_sikulix()
    open_clipboardXX()

def tear_down():
    close_clipboardXX()
    restore_existent_files()
    delete_new_files()
    print("Finished test")