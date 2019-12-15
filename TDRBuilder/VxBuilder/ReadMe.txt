================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : TDRBuilder Project Overview
===============================================================================

The application wizard has created this TDRBuilder application for 
you.  This application not only demonstrates the basics of using the Microsoft 
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your TDRBuilder application.

VxBuilder.vcproj
    This is the main project file for VC++ projects generated using an application wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    application wizard.

VxBuilder.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CTDRBuilderApp application class.

VxBuilder.cpp
    This is the main application source file that contains the application
    class CTDRBuilderApp.

VxBuilder.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\VxBuilder.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file VxBuilder.rc.

res\VxBuilder.rc2
    This file contains resources that are not edited by Microsoft 
    Visual C++. You should place all resources not editable by
    the resource editor in this file.
VxBuilder.reg
    This is an example .reg file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .reg
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.
/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    The project includes a standard MFC interface.
MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.
res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in VxBuilder.rc to add
    toolbar buttons.

res\IToolbar.bmp
    This bitmap file is used to create tiled images for the toolbar
    when your server application is in-place activated inside another
    container. This toolbar is constructed in the CInPlaceFrame
    class. This bitmap is similar to the bitmap in res\Toolbar.bmp
    except that it has many nonserver commands removed.

/////////////////////////////////////////////////////////////////////////////

For the child frame window:

ChildFrm.h, ChildFrm.cpp
    These files define and implement the CChildFrame class, which
    supports the child windows in an MDI application.

/////////////////////////////////////////////////////////////////////////////

The application wizard creates one document type and one view:

VxBuilderDoc.h, VxBuilderDoc.cpp - the document
    These files contain your CTDRBuilderDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CTDRBuilderDoc::Serialize).
VxBuilderView.h, VxBuilderView.cpp - the view of the document
    These files contain your CTDRBuilderView class.
    CTDRBuilderView objects are used to view CTDRBuilderDoc objects.
res\VxBuilderDoc.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the CVxBuilderDoc class.  This icon is included by the main
    resource file VxBuilder.rc.
/////////////////////////////////////////////////////////////////////////////

The application wizard has also created classes specific to OLE

SrvrItem.h, SrvrItem.cpp
    These files contain your CTDRBuilderSrvrItem. This class is used to
    connect your CTDRBuilderDoc class to the OLE system, and optionally
    provide links to your document.
IpFrame.h, IpFrame.cpp
    These files contain your CInPlaceFrame. This class is derived
    from COleIPFrameWnd and controls all frame features during in-place activation.
    The project has support for Compound files. The Compound-file format stores a document 
    that contains one or more Automation objects to one file and still allows access to 
    the it for the individual objects.
/////////////////////////////////////////////////////////////////////////////

Help Support:

hlp\VxBuilder.hhp
    This file is a help project file. It contains the data needed to
    compile the help files into a .chm file.

hlp\VxBuilder.hhc
    This file lists the contents of the help project.

hlp\VxBuilder.hhk
    This file contains an index of the help topics.

hlp\afxcore.htm
    This file contains the standard help topics for standard MFC
    commands and screen objects. Add your own help topics to this file.

hlp\afxprint.htm
    This file contains the help topics for the printing commands.

makehtmlhelp.bat
    This file is used by the build system to compile the help files.

hlp\Images\*.gif
    These are bitmap files required by the standard help file topics for
    Microsoft Foundation Class Library standard commands.

/////////////////////////////////////////////////////////////////////////////

Other Features:

ActiveX Controls
    The application includes support to use ActiveX controls.

Printing and Print Preview support
    The application wizard has generated code to handle the print, print setup, and print preview
    commands by calling member functions in the CView class from the MFC library.
/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named VxBuilder.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is in a 
language other than the operating system's current language, you will need 
to copy the corresponding localized resources MFC70XXX.DLL from the Microsoft
Visual C++ CD-ROM under the Win\System directory to your computer's system or 
system32 directory, and rename it to be MFCLOC.DLL.  ("XXX" stands for the 
language abbreviation.  For example, MFC70DEU.DLL contains resources 
translated to German.)  If you don't do this, some of the UI elements of 
your application will remain in the language of the operating system.

/////////////////////////////////////////////////////////////////////////////
