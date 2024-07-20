  #include <iostream>
  #include <cstdlib>
  #include <string>

  // Function to print the HTML form
  void print_html_form() {
      std::cout << R"(
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>User Management</title>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
     <!-- Favicon and Styles -->
    <link rel="icon" type="image/x-icon" href="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A">
    <link rel="stylesheet" href="../Elxtra/styles.css">

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" integrity="sha384-AYmEC3Yw5cVb3ZcuHtOA93w35dYTsvhLPVnYs9eStHfGJvOvKxVfELGroGkvsg+p" crossorigin="anonymous"/>
    <style>
      body, html {
        height: 100%;
        background-color: #f4f4f4;
        background-image: url(https://ideogram.ai/assets/image/lossless/response/sgYQvRzoRnuaXM-J9Ee5bQ);
        background-size: cover;
        background-image: no-repeat;
      }
      .center-box {
        display: flex;
        justify-content: center;
        align-items: center;
        height: 100%;
        color: #333;
        backgorund-color: white , 0.5;
      }
      .box {
        border: 1px solid #ddd;
        padding: 20px;
        border-radius: 8px;
        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        background: #fff;
      }
      .form {
    display: flex;
    flex-direction: column;
    gap: 10px;
    padding-left: 2em;
    padding-right: 2em;
    padding-bottom: 0.4em;
    background-color: #171717;
    border-radius: 25px;
    transition: 0.4s ease-in-out;
  }

  .card {
    display: flex;
    justify-content: center;
  background-image: linear-gradient(163deg, #ca0404 0%, #05020dad 100%);
    border-radius: 22px;
    transition: all 0.3s;
    height: max-content;
  }

  .card2 {
    border-radius: 0;
    transition: all 0.2s;
  }

  .card2:hover {
    transform: scale(0.98);
    border-radius: 20px;
  }

  .card:hover {
    box-shadow: 0px 0px 30px 1px rgba(255, 25, 0, 0.3);
  }

  #heading {
    text-align: center;
    margin: 2em;
    color: rgb(255, 255, 255);
    font-size: 1.2em;
  }

  .field {
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 0.5em;
    border-radius: 25px;
    padding: 0.6em;
    border: none;
    outline: none;
    color: white;
    background-color: #171717;
    box-shadow: inset 2px 5px 10px rgb(5, 5, 5);
  }

  .input-icon {
    height: 1.3em;
    width: 1.3em;
    fill: white;
  }

  .input-field {
    background: none;
    border: none;
    outline: none;
    width: 100%;
    color: #d3d3d3;
  }

  .form .btn {
    display: flex;
    justify-content: center;
    flex-direction: row;
    margin-top: 2.5em;
  }

  .button1 {
    padding: 0.5em;
    padding-left: 1.1em;
    padding-right: 1.1em;
    border-radius: 5px;
    margin-right: 0.5em;
    border: none;
    outline: none;
    transition: 0.4s ease-in-out;
    background-color: #252525;
    color: white;
  }

  .button1:hover {
    background-color: black;
    color: white;
  }

  .button2 {
    padding: 0.5em;
    padding-left: 2.3em;
    padding-right: 2.3em;
    border-radius: 5px;
    border: none;
    outline: none;
    transition: 0.4s ease-in-out;
    background-color: #252525;
    color: white;
  }

  .button2:hover {
    background-color: black;
    color: white;
  }

  .button3 {
    margin-bottom: 3em;
    padding: 0.5em;
    border-radius: 5px;
    border: none;
    outline: none;
    transition: 0.4s ease-in-out;
    background-color: #252525;
    color: white;
  }

  .button3:hover {
    background-color: red;
    color: white;
  }

    </style>
    </head>
    <header id="navbar" class="fixed-top navbar navbar-expand-md navbar-dark fade-down">
            <div class="container-fluid">
                <a class="navbar-brand d-flex gap-3 align-items-center" href="#">
                    <img src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="" width="30" height="24" class="d-inline-block align-text-top">
                    <h1 class="display-4 fs-4 m-3">Elxtra</h1>
                </a>
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <nav class="collapse navbar-collapse" id="navbarSupportedContent">
                <ul class="navbar-nav me-auto">
                <li class="nav-item">
                    <a class="nav-link p-0 m-3 active" aria-current="page" href="/">Home</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="#">About Us</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="#" tabindex="-1" aria-disabled="true">Contact Us</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="#" tabindex="-1" aria-disabled="true">FAQs</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="#" tabindex="-1" aria-disabled="true">Car Models</a>
                </li>
                </ul>
                <div class="d-flex">
                <a class="btn m-3 btn-outline-primary text-light fw-bold border-light">Login</a>
                </div>
            </nav>
            </div>
        </header>
  <body class="min-vh-100 d-flex align-items-center justify-content-center">
  <div class="card">
    <div class="card2">
      <form class="form">
        <p id="heading">Login</p>
        <div class="field">
          <svg
            viewBox="0 0 16 16"
            fill="currentColor"
            height="16"
            width="16"
            xmlns="http://www.w3.org/2000/svg"
            class="input-icon"
          >
            <path
              d="M13.106 7.222c0-2.967-2.249-5.032-5.482-5.032-3.35 0-5.646 2.318-5.646 5.702 0 3.493 2.235 5.708 5.762 5.708.862 0 1.689-.123 2.304-.335v-.862c-.43.199-1.354.328-2.29.328-2.926 0-4.813-1.88-4.813-4.798 0-2.844 1.921-4.881 4.594-4.881 2.735 0 4.608 1.688 4.608 4.156 0 1.682-.554 2.769-1.416 2.769-.492 0-.772-.28-.772-.76V5.206H8.923v.834h-.11c-.266-.595-.881-.964-1.6-.964-1.4 0-2.378 1.162-2.378 2.823 0 1.737.957 2.906 2.379 2.906.8 0 1.415-.39 1.709-1.087h.11c.081.67.703 1.148 1.503 1.148 1.572 0 2.57-1.415 2.57-3.643zm-7.177.704c0-1.197.54-1.907 1.456-1.907.93 0 1.524.738 1.524 1.907S8.308 9.84 7.371 9.84c-.895 0-1.442-.725-1.442-1.914z"
            ></path>
          </svg>
          <input
            type="text"
            class="input-field"
            placeholder="Username"
            autocomplete="off"
          />
        </div>
        <div class="field">
          <svg
            viewBox="0 0 16 16"
            fill="currentColor"
            height="16"
            width="16"
            xmlns="http://www.w3.org/2000/svg"
            class="input-icon"
          >
            <path
              d="M8 1a2 2 0 0 1 2 2v4H6V3a2 2 0 0 1 2-2zm3 6V3a3 3 0 0 0-6 0v4a2 2 0 0 0-2 2v5a2 2 0 0 0 2 2h6a2 2 0 0 0 2-2V9a2 2 0 0 0-2-2z"
            ></path>
          </svg>
          <input type="password" class="input-field" placeholder="Password" />
        </div>
        <div class="btn">
          <button class="button1">
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Login&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </button>
          <button class="button2">Sign Up</button>
        </div>
        <button class="button3">Forgot Password</button>
      </form>
    </div>
  </div>


  </body>
  </html>
  )";
  }

  // Function to decode URL-encoded strings
  std::string url_decode(const std::string& str) {
      std::string result;
      char ch;
      int i, ii;
      for (i = 0; i < str.length(); i++) {
          if (str[i] == '%') {
              sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
              ch = static_cast<char>(ii);
              result += ch;
              i += 2;
          } else if (str[i] == '+') {
              result += ' ';
          } else {
              result += str[i];
          }
      }
      return result;
  }

  // Function to get POST data
  std::string get_post_data() {
      std::string post_data;
      char* content_length = getenv("CONTENT_LENGTH");
      if (content_length) {
          int len = atoi(content_length);
          for (int i = 0; i < len; ++i) {
              char ch;
              std::cin.get(ch);
              post_data += ch;
          }
      }
      return post_data;
  }

  // Function to get form value
  std::string get_form_value(const std::string& data, const std::string& key) {
      std::string key_eq = key + "=";
      size_t start = data.find(key_eq);
      if (start != std::string::npos) {
          start += key_eq.length();
          size_t end = data.find("&", start);
          return url_decode(data.substr(start, end - start));
      }
      return "";
  }

  // Function to print result
  void print_result(const std::string& username, const std::string& password, const std::string& remember) {
      std::cout << "Content-type: text/html\r\n\r\n";
      
      const std::string correct_username = "admin";
      const std::string correct_password = "password";

      if (username == correct_username && password == correct_password) {
          // Successful login
          std::cout << R"(
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login Successful</title>
    <meta http-equiv="refresh" content="2;url=/cgi-bin/index.cgi">
    <link href="https://ideogram.ai/assets/image/lossless/response/sgYQvRzoRnuaXM-J9Ee5bQ" rel="stylesheet">
    <style>
      body, html {
        height: 100%;
        background-color: #f4f4f4;
      }
      .center-box {
        display: flex;
        justify-content: center;
        align-items: center;
        height: 100%;
        color: #333;
      }
      .box {
        border: 1px solid #ddd;
        padding: 20px;
        border-radius: 8px;
        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        background: #fff;
      }
    </style>
  </head>
  <body>

  <div class="container center-box">
    <div class="box">
      <h2>Login Successful</h2>
      <p>Redirecting to the home page...</p>
    </div>
  </div>

  </body>
  </html>
  )";
      } else {
          // Failed login
          std::cout << R"(
  <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login Failed</title>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
    <style>
      body, html {
        height: 100%;
        background-color: #f4f4f4;
        background-image: url(https://ideogram.ai/assets/image/lossless/response/AteFoH4WSjK6ToW5HkWPfw);
        background-size: cover;
        background-image: no-repeat;
      }
      .center-box {
        display: flex;
        justify-content: center;
        align-items: center;
        height: 100%;
        color: #333;
      }
      .box {
        border: 1px solid #ddd;
        padding: 20px;
        border-radius: 8px;
        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        background: #fff;
      }
    </style>
  </head>
  <body>

  <div class="container center-box">
    <div class="box">
      <h2>Login Failed</h2>
      <p>Invalid username or password.</p>
      <a href="/cgi-bin/summative.cgi" class="btn btn-primary">Back</a>
    </div>
  </div>

  </body>
  </html>
  )";
      }
  }

  int main() {
      std::cout << "Content-type: text/html\r\n\r\n";

      const char* request_method = getenv("REQUEST_METHOD");
      if (request_method && std::string(request_method) == "POST") {
          std::string post_data = get_post_data();
          std::string username = get_form_value(post_data, "username");
          std::string password = get_form_value(post_data, "password");
          std::string remember = get_form_value(post_data, "remember");
          
          print_result(username, password, remember);
      } else {
          print_html_form();
      }
      
      return 0;
  }
