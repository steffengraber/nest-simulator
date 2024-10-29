from setuptools import find_packages, setup

setup(
    cmake_source_dir=".",
    name="nest-simulator",
    # version='0.1.0',
    # ... other setup.py details ...
    # Install `modify_activate.py` as a script
    install_scripts=["build_support/modify_activate.py"],
    # Define an entry point to automatically run `modify_activate` after installation
    entry_points={
        "console_scripts": [
            "post-install-activate = build_support.modify_activate:main",
        ],
    },
)
