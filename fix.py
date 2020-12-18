import os

path = os.getcwd()
dirs = [os.path.join(path, f) for f in os.listdir(path)]
exclude = ['.git', 'node_modules', '.idea']

for i in dirs:
    file = dirs.pop(0)
    if os.path.isdir(file) and os.path.split(file)[-1] not in exclude:
        dirs.extend([os.path.join(file, f) for f in os.listdir(file)])
    elif file.endswith('.md'):
        os.system(f'yarn lint-md "{file}" --fix')
