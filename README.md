# Bluecadet Cinder Views Templates
Last updated 02/27/17

### How to install templates?
Take the ```.zip``` files from ```/template_exports``` and copy them into ```Documents/Visual Studio 2015/Templates/ItemTemplates```

### How to export templates?
1. File
2. Export Templates
3. Select Item Template
4. Next
5. Select the Source file you want to export
	- Unfortunately it seems as though you can only select one at a time
	- Source file you want isn't showing up? For some reason it seems that the file must be located in the vc2013 folder for it to be able to export.
6. Next
7. Next
8. Give your template a name, description, icon image, ect.
9. Next
        
Your template should be exported to `/template_export` and auto exported to your `Documents/Visual Studio 2015/Templates/ItemTemplate`
        
### What template variables can I use?
See [this](https://msdn.microsoft.com/en-us/library/eehb4faa.aspx) handy guide on Template Parameters. 
That being said, you cannot use `$safeprojectname$` as this is a variable create on new project creation and since we use TinderBox to create a project it does not seem to set this variable.