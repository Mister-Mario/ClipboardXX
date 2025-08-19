import json
import os

_paths = None
_paths_file_path = "..\\paths.json"

def _load_config():
    global _paths

    try:
        utils_dir_path = os.path.dirname(os.path.abspath(__file__)) #utils
        file_path = os.path.join(utils_dir_path, _paths_file_path)
        with open(file_path, 'r') as f:
            _paths = json.load(f)

    except Exception as e:
        print("ERROR: ", e) 
        _paths = {}

def get_from_paths(key):
    if _paths == None:
        _load_config()
    return _paths.get(key)

def get_shortcuts_path():
    return get_from_paths("shortcuts_path")

def get_app_exe_path():
    return get_from_paths("app_exe_path")

def get_sikulix_jar_path():
    return get_from_paths("sikuli_jar_path")