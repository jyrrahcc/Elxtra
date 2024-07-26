#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <utility>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <cmath>
#include "user.h"
#include "userdatabase.h"
using namespace std;

// Function to decode URL-encoded strings
string urlDecode(const string& str) {
    string result;
    char hex[3] = {0};
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '%') {
            if (i + 2 < str.length()) {
                hex[0] = str[i + 1];
                hex[1] = str[i + 2];
                result += static_cast<char>(strtol(hex, nullptr, 16));
                i += 2;
            }
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
}

// Function to parse query string into a key-value map
map<string, string> parseQueryString(const string& query) {
    map<string, string> params;
    string key, value;
    istringstream queryStream(query);
    while (getline(queryStream, key, '=')) {
        if (getline(queryStream, value, '&')) {
            params[urlDecode(key)] = urlDecode(value);
        }
    }
    return params;
}

// Function to parse cookies
map<string, string> parse_cookies(const string &cookie_header) {
    map<string, string> cookies;
    size_t pos = 0;
    string token;
    string header = cookie_header;
    while ((pos = header.find("; ")) != string::npos) {
        token = header.substr(0, pos);
        size_t eq_pos = token.find("=");
        if (eq_pos != string::npos) {
            string key = token.substr(0, eq_pos);
            string value = token.substr(eq_pos + 1);
            cookies[key] = value;
        }
        header.erase(0, pos + 2);
    }
    if ((pos = header.find("=")) != string::npos) {
        string key = header.substr(0, pos);
        string value = header.substr(pos + 1);
        cookies[key] = value;
    }
    return cookies;
}

// Function to print the HTML form
void print_html_form(const string &styleSheetContent, const string &username, const string &password, const string &remember, const string &invalid) {
    cout << "Content-type: text/html\r\n\r\n";
    cout << R"(
 <!DOCTYPE html>
  <html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login - Elxtra Motors</title>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
     <!-- Favicon and Styles -->
    <link rel="icon" type="image/x-icon" href="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A">
    <style>)" + styleSheetContent + R"(</style>

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" integrity="sha384-AYmEC3Yw5cVb3ZcuHtOA93w35dYTsvhLPVnYs9eStHfGJvOvKxVfELGroGkvsg+p" crossorigin="anonymous"/>

    <style>
      body, html {
        height: 100%;
        background-color: #f4f4f4;
        background-image: url(https://ideogram.ai/assets/image/lossless/response/sgYQvRzoRnuaXM-J9Ee5bQ);
        background-size: cover;
        background-position: center;
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
    <!-- Navbar -->
      <header id="navbar" class="fixed-top header navbar navbar-expand-md navbar-dark fade-down">
        <div class="container-fluid">
          <a class="navbar-brand d-flex align-items-center" href="#">
            <img src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="" width="30" height="24" class="d-inline-block align-text-top">
            <h1 class="display-4 fs-4 m-3">Elxtra</h1>
          </a>
          <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
          </button>
          <nav class="collapse navbar-collapse" id="navbarSupportedContent">
            <ul class="navbar-nav me-auto">
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./index.cgi">Home</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./aboutus.cgi">About Us</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./contactus.cgi">Contact Us</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./carmodels.cgi">Car Models</a>
                </li>
                </ul>
                </nav>
        </div>
      </header>
  <body class="min-vh-100 d-flex align-items-center justify-content-center">
  <div class="card">
    <div class="card2">
      <form class="form" method="POST">
                    <h2 class="text-light my-4">Login</h2>
                    <div class="field">
                        <svg viewBox="0 0 16 16" fill="currentColor" height="16" width="16" xmlns="http://www.w3.org/2000/svg" class="input-icon">
                            <path d="M13.106 7.222c0-2.967-2.249-5.032-5.482-5.032-3.35 0-5.646 2.318-5.646 5.702 0 3.493 2.235 5.708 5.762 5.708.862 0 1.689-.123 2.304-.335v-.862c-.43.199-1.354.328-2.29.328-2.926 0-4.813-1.88-4.813-4.798 0-2.844 1.921-4.881 4.594-4.881 2.735 0 4.608 1.688 4.608 4.156 0 1.682-.554 2.769-1.416 2.769-.492 0-.772-.28-.772-.76V5.206H8.923v.834h-.11c-.266-.595-.881-.964-1.6-.964-1.4 0-2.378 1.162-2.378 2.823 0 1.737.957 2.906 2.379 2.906.8 0 1.415-.39 1.709-1.087h.11c.081.67.703 1.148 1.503 1.148 1.572 0 2.57-1.415 2.57-3.643zm-7.177.704c0-1.197.54-1.907 1.456-1.907.93 0 1.524.738 1.524 1.907S8.308 9.84 7.371 9.84c-.895 0-1.442-.725-1.442-1.914z"></path>
                        </svg>
                        <input class="input-field" min="4" max="20" type="text" name="username" value=")" << username << R"(" placeholder="Username" required>
                    </div>
                    <div class="field">
                        <svg viewBox="0 0 16 16" fill="currentColor" height="16" width="16" xmlns="http://www.w3.org/2000/svg" class="input-icon">
                            <path d="M8 1a2 2 0 0 1 2 2v4H6V3a2 2 0 0 1 2-2zm3 6V3a3 3 0 0 0-6 0v4a2 2 0 0 0-2 2v5a2 2 0 0 0 2 2h6a2 2 0 0 0 2-2V9a2 2 0 0 0-2-2z"></path>
                        </svg>
                        <input class="input-field" type="password" name="password" value=")" << password << R"(" placeholder="Password" required>
                    </div>
                    )" + 
    (invalid != "" ? 
          "<p class='text-danger m-0 text-center'>" + invalid +"</p>" : "") + R"(
                    <div class="form-check ms-2 my-1">
                        <input class="form-check-input bg-danger border-light" type="checkbox" name="remember" id="remember" )" << ((remember == "true") ? "checked" : "") << R"(>
                        <label class="form-check-label text-light" for="remember">
                            Remember Me
                        </label>
                    </div>
                    <button class="btn btn-outline-danger my-3 fw-bold text-light border-light" type="submit">Login</button>
                </form>
    </div>
  </div>
  <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.min.js" integrity="sha384-cVKIPhGWiC2Al4u+LWgxfKTRIcfu0JTxR+EQDz/bgldoEyl4H0zUF0QKbrJ0EcQF" crossorigin="anonymous"></script>
  <script>
        const navbar = document.getElementById('navbar');

        window.addEventListener('resize', () => {
          if (window.innerWidth < 768) {
            navbar.classList.add('bg-dark');
          } else {
            navbar.classList.remove('bg-dark');
          }
        });
      </script>
  </body>
  </html>
)";
}

int main() {
    UserDatabase userDatabase;
    // Read the contents of the style sheet file
    ifstream styleSheetFile("./styles.css");
    string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
    styleSheetFile.close();
    // Get the request method
    string requestMethod = getenv("REQUEST_METHOD");
    // Read environment variables for cookie and query string
    string cookie_header = getenv("HTTP_COOKIE") ? getenv("HTTP_COOKIE") : "";
    map<string, string> cookies = parse_cookies(cookie_header);
    string name;
    // Check if the user is logged in
    if (requestMethod == "GET") {
      if (cookies.find("name") != cookies.end()) {
          cout << "Location: index.cgi\r\n\r\n";
      }
    }

    string invalid;
    string username;
    string password;
    string remember;

    if (requestMethod == "POST") {
        string contentLengthStr = getenv("CONTENT_LENGTH");
        // Check if the content length is not empty
        if (!contentLengthStr.empty()) {
            int contentLength = stoi(contentLengthStr);
            string postBody;
            postBody.resize(contentLength);
            cin.read(&postBody[0], contentLength);
            map<string, string> postParams = parseQueryString(postBody);
            // Cbecks if the search query is not empty
            if (postParams.find("username") != postParams.end() && postParams.find("password") != postParams.end()) {
              username = postParams["username"];
              password = postParams["password"];
              // Get the current time, then subtract enough time to ensure the cookie is in the past
              time_t now = time(0);
              struct tm tm = *gmtime(&now);
              tm.tm_hour -= 1; // Subtract 1 hour from the current time
              char buf[128];
                strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S GMT", &tm);
              const int MIN_USERNAME_LENGTH = 4;
              const int MAX_USERNAME_LENGTH = 20;
                if (username.length() >= MIN_USERNAME_LENGTH && username.length() <= MAX_USERNAME_LENGTH) {
                  bool hasSpecialChars = false;
                  for (char c : username) {
                    if (!isalnum(c)) {
                      hasSpecialChars = true;
                      break;
                    }
                  }
                  if (!hasSpecialChars) {
                    // Check credentials
                    if (userDatabase.getUserByUsername(username) != nullptr && userDatabase.getUserByUsername(username)->getPassword() == password) {
                        cout << "Set-Cookie: name=" << username << "; path=/; HttpOnly\r\n";
                        
                        if (postParams.find("remember") != postParams.end()) {
                          remember = true;
                          cout << "Set-Cookie: username=" << username << "; path=/; HttpOnly\r\n";
                          cout << "Set-Cookie: password=" << password << "; path=/; HttpOnly\r\n";
                          cout << "Set-Cookie: remember=true; path=/; HttpOnly\r\n";
                        }
                        else {
                          cout << "Set-Cookie: username=; path=/; HttpOnly\r\n";
                          cout << "Set-Cookie: password=; path=/; HttpOnly\r\n";
                          cout << "Set-Cookie: remember=; path=/; HttpOnly\r\n";
                        }
                        // Redirect to home page
                        cout << "Location: index.cgi\r\n\r\n";
                    }
                    else {
                        // Invalid credentials, show login page with error
                        invalid = "Invalid username or password";
                        print_html_form(styleSheetContent, username, password, remember, invalid);
                    }
                  } else {
                    // Invalid username, show login page with error
                    invalid = "Username should not contain special characters.";
                    print_html_form(styleSheetContent, username, password, remember, invalid);
                  }
                } else {
                  // Invalid username length, show login page with error
                  invalid = "Username should be between " + to_string(MIN_USERNAME_LENGTH) + " and " + to_string(MAX_USERNAME_LENGTH) + " characters.";
                  print_html_form(styleSheetContent, username, password, remember, invalid);
                }
            }
            else {
              // Generate the login page with prefilled fields
              print_html_form(styleSheetContent, username, password, remember, invalid);
            }
        } 
        else {
          // Generate the login page with prefilled fields
          print_html_form(styleSheetContent, username, password, remember, invalid);
        }
    }
    else {
      // Generate the login page with prefilled fields
      // Check cookies for "Remember Me"
      string username;
      string password;
      string remember;
      if (cookies.find("username") != cookies.end()) {
          username = cookies["username"];
      }
      if (cookies.find("password") != cookies.end()) {
          password = cookies["password"];
      }
      if (cookies.find("remember") != cookies.end()) {
          remember = cookies["remember"];
      }
      print_html_form(styleSheetContent, username, password, remember, invalid);
    }
    return 0;
}