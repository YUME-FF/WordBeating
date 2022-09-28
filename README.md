# WordBeating
## E-dictionary
- This program is designed to be written in C++ language, establishes a dialog-based MFC program, and connects to MySQL and ODBC databases and data sources.
- Mainly applied to the inheritance and overloading of classes; the use of dialog boxes; the use of MFC controls; the beautification of controls; custom messages; the use of threads and thread communication; DLL packaging and calling; Finally, an electronic dictionary program with many functions and beautiful appearance is realized.

## E-dictionary Interface
### Word Translation



## Function
- Through the native ODBC data source, create a new MySQL-based data table in navicat, the table name is word, and there are two columns in the table, the first column is word, the column name is Vocabulary, the second column is translation, and the column name is Meaning. And import about 1000 English words and their corresponding Chinese-English translations into the data table in advance.

- The design is based on the database programming environment built by the static library technology, which can connect to the database through the user port name, table name, and corresponding password; at the same time, the MySQL statement is used for programming, which realizes the acquisition, editing, deletion, Added the ability to add content in the data table.

- The design mainly realizes the dictionary maintenance function based on MySQL statement using database programming technology, which mainly includes the addition and deletion of words, and the modification and editing of word English or Chinese recitation methods.

- The design mainly realizes the user query function based on the MySQL statement using the database programming technology, mainly including the user inputting Chinese to get the corresponding English interpretation, and the user inputting English to get the corresponding Chinese interpretation.

- The design also adds an advertisement field, and uses the DLL encapsulation and invocation to realize the function of clicking on the advertisement and jumping to the corresponding website.

- The design uses threads and custom messages to realize the timing and rolling playback of advertisements, and the timing period is set to 5s.

- The main MFC controls involved in this design are: Tab Control, List Control, Picture Control, Button, Static Text and so on.

- The interface and controls of the design have been fully beautified, mainly involving the beautification of Bitmap, Icon and other resources, and the use of Photoshop and the image editing tools that come with Visual Studio 2019 for image beautification and many other operations.

## Functional Description — Script Structure

<img src="https://github.com/YUME-FF/WordBeating/blob/main/images/Structure.png" width="1000px">


## Functional Description — Function Variable Architecture

<img src="https://github.com/YUME-FF/WordBeating/blob/main/images/Variable%20Architecture.png" width="1000px">
