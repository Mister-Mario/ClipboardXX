import sys
import os

script_path = getBundlePath()

parent_path = os.path.abspath(os.path.join(script_path, "..\\.."))

if parent_path not in sys.path:
    sys.path.append(parent_path)

from utils import utils, navigation, paths
try:
    utils.set_up()

    App.open(utils.get_test_files_path() + "\\LoremIpsum.txt")
    wait(1)#Cannot tell which text editor will be used
    
    #Select Lorem word and copy
    doubleClick(utils.create_img("External\\LoremWord.png"))
    wait(1)
    navigation.bring_forward_shortcut()
    #Copy button for memory cell 1
    memory_cell_1_region = find(utils.create_img("MemoryCell1.png"))
    click(memory_cell_1_region.center.offset(320, 0))
    
    click()#Deselects word
    App(paths.get_text_editor_name()).closeByKey()

    #Export file
    navigation.bring_forward_tray_icon()
    navigation.go_to_main_window_from_shortcuts()
    navigation.go_to_export()
    utils.export_file("ST5_export.txt",".")

    if(not utils.compare_files(utils.get_test_files_path() + "\\ST4_1_export_expected.txt",
                            utils.get_test_files_path() + "\\ST5_export.txt")):
        raise ValueError("Files are not the same")

    App.open(utils.get_test_files_path() + "\\Blank.txt")
    wait(1)#Cannot tell which text editor will be used
    
    navigation.bring_forward_shortcut()
    #Paste button for memory cell 1
    memory_cell_1_region = find(utils.create_img("MemoryCell1Lorem.png"))
    click(memory_cell_1_region.center.offset(400, 0))
    wait(0.5)
    #Save file
    type("s", Key.CTRL)

    if(not utils.compare_files(utils.get_test_files_path() + "\\ST4_2_export_expected.txt",
                            utils.get_test_files_path() + "\\Blank.txt")):
        raise ValueError("Files are not the same")

except Exception as e:
    keyUp(Key.CTRL)
    print("Test Failed, capturing actual screen")
    print(e)
    ruta_captura = capture(SCREEN)
    print("Path of screen capture", ruta_captura)

finally:
    utils.tear_down()