import sys

effectName = raw_input()
description = raw_input()
moduleTypesFile = '../../shared/CoreModules/moduleTypes.h'
coreTemplate = 'coreTemplate.cpp'
moduleWidgetTemplate = 'wrapperTemplate.cpp'
plugincpp = '../src/plugin.cpp'
pluginhpp = '../src/plugin.hpp'
pluginjson = '../plugin.json'

# Read in the file
with open(moduleTypesFile, 'r') as file :
  filedata = file.read()

# Replace the target string
newText = 'PANEL, \n'
newText += effectName + ','
filedata = filedata.replace('PANEL,', newText.upper())

# Write the file out again
with open(moduleTypesFile, 'w') as file:
  file.write(filedata)

with open(coreTemplate, 'r') as file :
  filedata = file.read()

# Replace the target string
newText = ''
newText = effectName.capitalize()
modelName = 'model' + newText

newText+='Core'

filedata = filedata.replace('TemplateCore', newText)
filedata = filedata.replace('SLUG',effectName.upper())
filedata = filedata.replace('DESCRIPTION',description)

newCoreFileName='../../shared/CoreModules/' + effectName.lower()+'Core.h'

# Write the file out again
with open(newCoreFileName, 'w') as file:
  file.write(filedata)

newCoreCPP = '../../shared/CoreModules/' + effectName.lower()+'Core.cpp'

with open(newCoreCPP,'w') as file:
  file.write("#include " + '\"' + effectName.lower()+'Core.h' + '\"')

with open(plugincpp, 'r') as file :
  filedata = file.read()

newText = 'Add modules here \n' + '\tp->addModel(' + modelName + ');'
filedata=filedata.replace('Add modules here',newText)

with open(plugincpp, 'w') as file:
  file.write(filedata)

with open(pluginhpp, 'r') as file:
  filedata = file.read()

newText = 'module source file \n' + 'extern Model *' + modelName + ';'
filedata = filedata.replace('module source file',newText)

with open(pluginhpp, 'w') as file:
  file.write(filedata)

with open(moduleWidgetTemplate, 'r') as file:
  filedata = file.read()

filedata = filedata.replace('Template',effectName.capitalize())
filedata = filedata.replace('template',effectName.lower())
filedata = filedata.replace('EFFECTNAME',effectName.upper())
filedata = filedata.replace('MODULENAME','*' + modelName)
filedata = filedata.replace('SLUG','\"' + effectName.upper() + '\"')

newWrapper = '../src/' + effectName.lower()+'Module.cpp'

with open(newWrapper, 'w') as file:
  file.write(filedata)

with open(pluginjson, 'r') as file:
  filedata= file.read()

with open('jsonTemplate.txt', 'r') as jsonTemp:
  jsondata = jsonTemp.read()

jsondata = jsondata.replace('slugTemplate',effectName.upper())
jsondata = jsondata.replace('nameTemplate',effectName.capitalize())
jsondata = jsondata.replace('MODULEDESCRIPTION',description)

newText = '"modules": [ \n' + jsondata
filedata = filedata.replace('"modules": [',newText)

with open(pluginjson, 'w') as file:
  file.write(filedata)
