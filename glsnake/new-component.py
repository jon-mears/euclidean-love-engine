import os
import sys
import xml.etree.ElementTree as ET

def GenerateHeaderGuard(component : str) -> str:
    guard = ''
    for i in range(len(component)):
        guard += component[i]

        if i != len(component)-1:
            if component[i+1].isupper():
                guard += '_'

    guard = guard.upper()

    guard += '_HPP'

    return guard

def GenerateHPPFilename(component : str) -> str:
    filename = ''
    
    for i in range(len(component)):
        filename += component[i]
        if i < len(component)-1:
            if component[i+1].isupper():
                filename += '-'
    
    filename = filename.lower()
    filename += '.hpp'

    return filename

def GenerateHPPFileContent(component : str) -> str:
    guard = GenerateHeaderGuard(component)

    file = \
    f'''#ifndef {guard}
#define {guard}

#include "component.hpp"
class GameObject;

class {component} : public Component {{
private:

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    {component}(GameObject* pGO);
}};
#endif'''

    return file

def GenerateCPPFilename(component : str) -> str:
    filename = ''
    
    for i in range(len(component)):
        filename += component[i]
        if i < len(component)-1:
            if component[i+1].isupper():
                filename += '-'
    
    filename = filename.lower()
    filename += '.cpp'

    return filename

def GenerateCPPFileContent(component: str) -> str:
    hpp = GenerateHPPFilename(component)
    
    file = \
    f'''#include \"{hpp}\"
#include \"component.hpp\"

void {component}::Start() {{
    
}}

void {component}::Update() {{
    
}}

void {component}::ConstUpdate() const {{
    
}}

{component}::{component}(GameObject* pGO) : Component(pGO) {{ }}
    '''

    return file

if __name__ == '__main__':
    if (len(sys.argv) < 2):
        print('must provide component filename!')
        exit()

    component = sys.argv[1].strip()
    pos = component.find('Component')

    if pos == -1 or pos != len(component) - 9:
        component += 'Component'

    hpp_filename = GenerateHPPFilename(component)
    cpp_filename = GenerateCPPFilename(component)

    hpp = GenerateHPPFileContent(component)
    cpp = GenerateCPPFileContent(component)

    if (os.path.isfile(hpp_filename)):
        pass
    else:
        file = open(hpp_filename, 'w')
        file.write(hpp)
        file.close()

    if (os.path.isfile(cpp_filename)):
        pass
    else:
        file = open(cpp_filename, 'w')
        file.write(cpp)
        file.close()

    # write to the vcxproj file
    ET.register_namespace('', 'http://schemas.microsoft.com/developer/msbuild/2003')
    tree = ET.parse('./glsnake.vcxproj')
    root = tree.getroot()

    for child in root:
        if child.tag[child.tag.find('}')+1:] == 'ItemGroup':
            if child[0].tag[child.tag.find('}')+1:] == 'ClInclude':
                e = ET.Element('ClInclude', {'Include': hpp_filename})
                child.append(e)
            
            elif child[0].tag[child.tag.find('}')+1:] == 'ClCompile':
                e = ET.Element('ClCompile', {'Include': cpp_filename})
                child.append(e)

    tree.write('glsnake.vcxproj')

    # write to the vcxproj.filters file
    ET.register_namespace('', 'http://schemas.microsoft.com/developer/msbuild/2003')
    tree = ET.parse('./glsnake.vcxproj.filters')
    root = tree.getroot()

    for child in root:
        if child.tag[child.tag.find('}')+1:] == 'ItemGroup':
            if child[0].tag[child.tag.find('}')+1:] == 'ClInclude':
                include_tag = ET.Element('ClInclude', {'Include': hpp_filename})
                filter_tag = ET.Element('Filter')
                filter_tag.text = 'Header Files\\Components'
                include_tag.append(filter_tag)
                child.append(include_tag)

            elif child[0].tag[child.tag.find('}')+1:] == 'ClCompile':
                compile_tag = ET.Element('ClCompile', {'Include': cpp_filename})
                filter_tag = ET.Element('Filter')
                filter_tag.text = 'Source Files\\Components'
                compile_tag.append(filter_tag)
                child.append(compile_tag)

    tree.write('glsnake.vcxproj.filters')