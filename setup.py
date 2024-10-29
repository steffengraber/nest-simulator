from setuptools import find_packages, setup

setup(
    name="my_package",
    # version='0.1.0',
    # ... other setup.py details ...
    # Install `modify_activate.py` as a script
    install_scripts=["scripts/modify_activate.py"],
    # Define an entry point to automatically run `modify_activate` after installation
    entry_points={
        "console_scripts": [
            "post-install-activate = scripts.modify_activate:main",
        ],
    },
)
