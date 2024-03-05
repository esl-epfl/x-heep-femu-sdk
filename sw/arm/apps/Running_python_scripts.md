To run python scripts you need to

```sh
sudo su
cd x-heep-femu-sdk
source init.sh
```

Then you can either run a `.py` script by calling:
```sh
python3 sw/arm/apps/hello_world.py
```

or any notebook with

```sh
ipython -c "%run sw/arm/jupyter_notebooks/hello_world.ipynb"
```
or
```sh
ipython --TerminalIPythonApp.file_to_run=sw/arm/jupyter_notebooks/hello_world.ipynb
```
