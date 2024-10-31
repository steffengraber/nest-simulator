#!/usr/bin/env python
import os
import subprocess
import sys


def get_virtual_env_type(activate_path):
    """Detects the virtual environment type (venv, virtualenv, conda)."""
    # Check for venv, virtualenv, and conda by looking for common files
    venv_marker = os.path.join(os.path.dirname(activate_path), "pyvenv.cfg")
    virtualenv_marker = os.path.join(os.path.dirname(activate_path), "bin", "activate_this.py")
    conda_marker = os.path.join(os.path.dirname(activate_path), "conda-meta")

    if os.path.exists(venv_marker):
        return "venv"
    elif os.path.exists(virtualenv_marker):
        return "virtualenv"
    elif os.path.exists(conda_marker):
        return "conda"
    else:
        return None


def modify_activate(activate_path, env_type):
    """Modifies the activate script to set environment variables."""
    if env_type == "venv":
        with open(activate_path, "a") as f:
            f.write('\nexport PATH="${VIRTUAL_ENV}/lib/site-packages/bin:$PATH"\n')

    elif env_type == "virtualenv":
        with open(activate_path, "a") as f:
            f.write('\nMY_VAR="my_value"\n')
            f.write('ANOTHER_VAR="another_value"\n')
    elif env_type == "conda":
        with open(activate_path, "a") as f:
            f.write("\nMY_VAR='my_value'\n")
            f.write("ANOTHER_VAR='another_value'\n")
    else:
        print(f"Error: Could not determine virtual environment type. Aborting.")
        sys.exit(1)


if __name__ == "__main__":
    # Get the path to the activate script
    activate_path = os.path.join(os.environ["VIRTUAL_ENV"], "bin", "activate")

    # Detect virtual environment type
    env_type = get_virtual_env_type(activate_path)

    # Modify the activate script if the environment type is found
    if env_type:
        modify_activate(activate_path, env_type)
    else:
        print(f"Error: Could not determine virtual environment type. Aborting.")
        sys.exit(1)
