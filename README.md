# INITIAL PROBLEM AND PROJECT PURPOSE

To facilitate the work of those seeking to access information from ECHOLE 42 students and staff, the institution has developed an [official API](https://api.intra.42.fr/), where anyone with an access token can request this information and receive it.

However, the information is very detailed and deals with all public information of each user registered in Intra. In order to filter this information, I started to develop an API where the user can search for a user, and receive only important information for the analysis of student performance.

# STORED DATA

Before filtering the information, it was necessary to think on what information could be useful in the analysis of each student's performance. For this, the following information was initially stored in a general table:

- Login;
- ID;
- Full Name;
- Campus;
- Course Start Date;
- Level;
- Current Project;
- Graded Projects(Not Basecamp);
- Number of Badges;
- Evaluation Points;
- Wallet;
- Staff?;

Although this information shows the cadet's profile in general, it is still too superficial to analyze its performance in projects, so, for each requested profile, a **Project Table** is created, and stores details about each login project . This table is named after **ID** (ID_projects). Thus, with the student ID, it is possible to do a more in-depth analysis of their performance in projects since Basecamp. The information stored is:

- Project Name;
- Started at;
- Graded at(if graded);
- Status (Finished/In Progress);
- Retries;
- Final Grade;

**Information is updated with each request**

# Development Stages

For the project development, i defined some features that it should have, and divided into several stages.

- **Connection with the Intra API (working);**

	In this step, the **libcurl** library was used. This library allows making HTTP requests through a C program;

- **Receive and store information (working);**

	In this step, the `freopen` function was used to store the API response in a JSON file.

- **Parse useful information (working);**

	Through the **json-c** library it was possible to parse the information stored in the **response.json** file, which are stored before in structs declared on the `api.h` 	header.

- **Store the information in a Database (working);**

	Once parsed and stored in the structs, i made a connection to the database using the **my_sql** library. The program should inform you that the connection has been 		established and that the data has been stored.

- **Behave like an API, receiving requests and returning information (working);**

	After having all the data filtered and stored, it was necessary to connect a server in the local network, so it could be accessed, receive HTTP requests and return 		information. The connection was made through the **ulfius** library, which was developed to facilitate the construction of API in C.

- **Treat errors, leaks and unexpected behavior (in progress);**

## Dependencies and Use

**`ulfius` library and his dependencies, `json-c`, `mysql` e `libcurl` must be installed**

**Information refers to the current version**
Once ready to use and with the dependencies installed, just run `make` command and the program should compile, returning an **a.out** file. When executing it, a message on the terminal will inform you that the framework has been started. After making the HTTP request, with the address `http://localhost:8080/:user`, the user's login will be requested to the API of 42. If the user is found, the program will return the message `Data found`, ` Connection with Database Established` and `Data Stored`, and will return the parsed data in **json** format to the client. All data is stored in the database.

## Know Errors

- 404 Error : Data Not Found

	The login was not found.

- 403 Error!! Not Authorized

	Token is not valid

- 500 Error : Connection with 42API Failed!!

	The 42 API connection cannot be established.

## Detailed Functions

- `main`: Starts connection to the local network. It is this function that will receive the HTTP requests, run the `ft_request` function and callback the string to the client API.

- `ft_request`: Starts the connection with Curl, reads the Token and receives the requested login. After making the request to 42 API, it will store the content in the response.json file. After content confirmation, it calls the functions responsible for parsing and storing. Returns the string of information obtained in json format, or the error detected.

- `read_token`: Reads the .txt file, where the Token is stored. Should return the content in a string.

- `test_input`: Reads from the .json file, where the API response is stored. If it does not find the data or the access was denied, it will return a int informing the error. If no errors are found, it returns 0.

- `data_filter`: Open .json file and stores it in a buffer. Then it must perform a series of secondary functions, where each user's information is stored in the profile struct. If the login belongs to the Staff, it will only store name, ID and campus, in order to avoid crashes.

- `project_data`: Similar to `data_filter`, but it should only store the information referring to a certain project in the t_project struct. It will work in a loop parsing, storing in the struct, saving to the database and returning, one project at a time, until the oldest one. It is not performed if the login belongs to the Staff.

- `proj_db`: It is called at the beginning of the `project_data` function. Its job is to create a new Table, unique to each user, and erasing the oldest data.

- `populate_pdb`: It is called at each loop of the `project data` function. Since all data is stored at t_project struct, this function should store its contents in ID_projects table.

- `store_data`: Stores the profile struct data to the users Tables. Before storing, it erases old data to avoid duplicated insert.

- `ft_strjoin`: Used to concatenate strings. It is used to build the json callback that will be returned to the client.

- `ft_strnstr`: Used to parse data received in string format, search for a smaller string within a larger string within a number of characters, returning its position if found, or null if not found

- `write_profile`: Writes user information in a allocated memory address, respecting JSON format.

- `write_projects`: Writes the project information to a allocated memory address, respecting JSON format, always concatenating with the previous content.
