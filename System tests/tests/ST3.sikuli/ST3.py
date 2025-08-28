import sys
import os

script_path = getBundlePath()

parent_path = os.path.abspath(os.path.join(script_path, "..\\.."))

if parent_path not in sys.path:
    sys.path.append(parent_path)

from utils import utils, navigation, paths
try:
    utils.set_up()
    navigation.go_to_main_window_from_shortcuts()

    click(utils.create_img("MainView\\AutocopyOff.png"))
    wait(utils.create_img("MainView\\AutocopyOn.png"))

    App.open(utils.get_test_files_path() + "\\LoremIpsum.txt")
    wait(1)#Cannot tell which text editor will be used
    
    #Select Lorem word and copy
    doubleClick(utils.create_img("External\\LoremWord.png"))
    wait(1)
    type("c", Key.CTRL)
    click()#Deselects word
    App(paths.get_text_editor_name()).closeByKey()

    #Export file
    navigation.bring_forward_tray_icon()
    navigation.go_to_main_window_from_shortcuts()
    navigation.go_to_export()
    utils.export_file("ST3_1_export.txt",".")

    if(not utils.compare_files(utils.get_test_files_path() + "\\ST3_1_export_expected.txt",
                            utils.get_test_files_path() + "\\ST3_1_export.txt")):
        raise ValueError("Files are not the same")

    #Restart Clipboard++
    utils.close_clipboardXX()
    utils.open_clipboardXX()

    navigation.go_to_main_window_from_shortcuts()
    navigation.go_to_import()
    utils.import_file("FullMemoryCell.txt", ".")

    click(utils.create_img("MainView\\AutocopyOff.png"))
    wait(utils.create_img("MainView\\AutocopyOn.png"))

    App.open(utils.get_test_files_path() + "\\LoremIpsum.txt")
    wait(1)#Cannot tell which text editor will be used
    
    #Select Lorem word and copy
    doubleClick(utils.create_img("External\\LoremWord.png"))
    wait(1)
    type("c", Key.CTRL)
    click()#Deselects word
    App(paths.get_text_editor_name()).closeByKey()

    #Export file
    navigation.bring_forward_tray_icon()
    navigation.go_to_main_window_from_shortcuts()
    navigation.go_to_export()
    utils.export_file("ST3_2_export.txt",".")

    if(not utils.compare_files(utils.get_test_files_path() + "\\ST3_2_export_expected.txt",
                            utils.get_test_files_path() + "\\ST3_2_export.txt")):
        raise ValueError("Files are not the same")

except Exception as e:
    print("Test Failed, capturing actual screen")
    print(e)
    ruta_captura = capture(SCREEN)
    print("Path of screen capture", ruta_captura)

finally:
    utils.tear_down()