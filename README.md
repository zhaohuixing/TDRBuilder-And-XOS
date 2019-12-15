Note: All of the source code was developed between year 2000 and 2005 with Visual C++ and MFC, and may not be compiled with current Visual C++ compiler directly without modifications.

The code segment contains two parts of open source code which are based from same idea of building an OOP visual computing system

# 1. TDRBuilder:a Thinking-Drawing-Running (TDR) concept base computing software bridging the gap between desing and software programming.

In summer 2000, after many years of working in various industrial software projects, a thought came into my mind that the process of software product development should be more independent from programming technique so that more technical professional without specific programming skill can design and create the software application to implement their technical requirement by themselves.

With such idea, I develop the technology with concept of TDR (Thinking-Drawing-Running), which bridge the gap between current CASE tools and software programming tools.

The philosophy of “Thinking-Drawing-Running” (TDR) comes from my thought with regard to the software creation process:  

**•	Modern computer science technology could let more people, without special programming technical skill or knowledge, able to create software solution for their technical idea, design or algorithm easily; in other words, the software design and creation process should be more idea/design/algorithm oriented rather than programming technique oriented.**

**•	Modern software application design and creation process should be more visualized and more independent from programming technique/programming language.** 

**•	The software application creation process should be more naturally and directly reflecting the people's idea, design or algorithm rather than the demonstration of programming technique, skill or trick.** 

In the concept of “Thinking-Drawing-Running” (TDR), “Thinking” (T) indicates the people's technical idea, computing design or algorithm. “Drawing” (D) means that people can present implement or transform their technical idea, computing design or algorithm (“Thinking” (T)) by drawing the technical diagrams. “Running” (R) means that people can easily analyze, validate their design diagrams by compiling and running the design diagram, the result can be checked or verified by user.

The TDR combines general CASE technology and compiler technology together, it makes the software development by the way of “programming by diagramming”; the boundary between design and coding process will be blurred and the two processes will be melting together.

TDRBuilder is built on TDR technology base CASE and Computing solution software. With TDRBuilder, people can implement or transform their computing algorithm, technical design or idea by drawing the logical flowchart diagram, editing the computing/logical process in each flowchart block/step; people also can verify or check the result of their design by compiling and running their design module represented by the flowchart diagram.

The main functionalities of TDRBuilder are:

**•	Creating new/empty module flowchart diagram.**

**•	Adding, deleting, moving the processor block or block connector in flowchart diagram.**

**•	Adding, editing, and deleting the various variables in the flowchart diagram (the module presented by the flowchart diagram).**

**•	Adding, editing, deleting the computing processes (equations/functions) or logical comparison processes in each block.**

**•	Compiling the flowchart diagram (the module presented by the flowchart diagram) to validate the design logical or syntax correction.**

**•	Running/Operating the flowchart diagram (the module presented by the flowchart diagram) to verify the design result; or Running the diagram step by step and real-time checking each individual computing/logic block process result (like the Debug steps in most famous IDE).** 

**•	Saving the flowchart diagram (the module presented by the flowchart diagram) to disk files (XML format) which can be re-opened by TDRBuilder or run by TDRRun service.**

**•	Exporting the design and operating result of flowchart diagram (the module presented by the flowchart diagram) and to various format files including C++ class, text file, XML file, Microsoft Word and Excel file etc.**

**•	Printing out the design and operating result of flowchart diagram (the module presented by the flowchart diagram).**

**•	Copying and Pasting the flowchart diagram (the module presented by the flowchart diagram) or individual block in the flowchart diagram.**


The internal architecture of TDRBuilder software is that one software design diagram is built into one module; each process block in the diagram is created as the processor unit in the module.

# 2. XOS: An Object-Oriented Translation and Data Processing Module Design for Computer Programming Language Compiler or Interpreter

The object-oriented translation and data processing module presented in this document implements the functionalities of generic, common process of the translation, storage, interpretation or execution of data objects, including data object properties and behaviors, which are originated or generated from computer programming language source code scanners and parsers system, or command instruction from virtual machine service.

The object-oriented translation and data processing module in this document is designed based on the object-oriented programming technology, and completely followed the fundamental principles of the   object-oriented programming philosophy. In this design, any object is consisted of its property objects (generally called as class member data) and class behavior object (generally called as class member function); any object is assembled or manufactured by or with other objects either presenting the property of object (class member data) or presenting the behavior of object (class member function or class member function object). The traditional object-oriented programming concept of class member data and class member function is processed as the same in this design, where both of them are the objects which serve with different functionality in this system, one storing the owner object’s property information, the other acting the owner object’s behavior.   

In this design, late-bind technology is applied. During the compiling time, all objects, which information is scanned from source code, are fabricated into their own description object (or template object); in run time, the real object instance is created from the object’s description object, or the real object is bound or attached into the execution processing based on the information in its description object. 

