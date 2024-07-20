#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <map> 
#include <fstream>// Include the map header
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

int main() {
    cout << "Content-Type: text/html\n\n";

    // string method = getenv("REQUEST_METHOD");
    // string name;

    // if (method == "GET") {
    //     string query = getenv("QUERY_STRING");
    //     auto params = parseQueryString(query);
    //     if (params.find("name") != params.end()) {
    //         name = params["name"];
    //     }
    // } else if (method == "POST") {
    //     int contentLength = stoi(getenv("CONTENT_LENGTH"));
    //     string postData(contentLength, ' ');
    //     cin.read(&postData[0], contentLength);
    //     auto params = parseQueryString(postData);
    //     if (params.find("name") != params.end()) {
    //         name = params["name"];
    //     }
    // }

      // Read the contents of the style sheet file
      ifstream styleSheetFile("./styles.css");
      string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
      styleSheetFile.close();

      // Generate the HTML code
      string htmlCode = R"(<!DOCTYPE html>
    <html lang="en">
      <head>
      <!-- Document Metadata -->
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
      <meta name="author" content="John Yrrah Cabiles">

      <!-- Favicon and Styles -->
      <link rel="icon" type="image/x-icon" href="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A">
      <style>)" + styleSheetContent + R"(</style>

      <!-- Bootstrap CSS -->
      <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
      <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" integrity="sha384-AYmEC3Yw5cVb3ZcuHtOA93w35dYTsvhLPVnYs9eStHfGJvOvKxVfELGroGkvsg+p" crossorigin="anonymous"/>

      <!-- Page Title -->
      <title>Elxtra Motors</title>
      </head>
      <body>
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
      <main>
        <!-- Hero Section -->
        <section class="min-vh-100 cover">
          <section class="darkener boundary py-5 w-100 d-flex align-items-center justify-content-center">
            <section class="container">
              <section class="row">
                <section class="col-sm-8 fade-left">
                  <h2 class="display-3 text-light">Drive the Future with Elxtra Motors</h2>
                  <p class="lead text-light">At Elxtra Motors, we are redefining the automotive industry with our state-of-the-art electric vehicles. Our commitment to innovation and elegance sets us apart, offering you a driving experience like no other. Discover the future of transportation today with Elxtra.</p>
                  <a href="" class="btn btn-light text-danger fw-bold">Learn More</a>
                </section>
                <section class="col-sm-4">
                </section>
              </section>
            </section>
          </section>
          <div class="arrow d-none d-sm-flex" onclick='window.scrollBy(50, window.innerHeight)'>
          </div>
        </section>
        <section class="bg-dark">
          <section class="container w-100 text-center overflow-hidden position-relative py-2 d-flex gap-5 align-items-center justify-content-center">
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
          </section>
        </section>
        <section id="sticky-header" class="container-fluid py-2 text-center border-top border-5 border-bottom border-light">
          <h2><a href="#featured" class="text-light">Check Out Our Latest Innovations</a></h2>
         </section>
        <!-- Featured Content -->
        <section id="featured" class="container-fluid">
        <section class="row">
          <section class="col-lg-5 py-5 bg-dark border-5 rounded-circle rounded-bottom border-light">
          <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
            <h2 class="display-4 m-0 h1">Advanced Battery System</h2>
          </section>
          </section>
          <section class="col-lg-7 p-0 hello battery">
          <section class="h-100 d-flex flex-column p-md-5 p-2 text-light">
            <h2 class="display-4">Advanced Battery System</h2>
            <p class="lead">At Elextra Motors, we are committed to pushing the boundaries of electric vehicle technology. Our latest battery system exemplifies this commitment by offering an impressive combination of extended range and rapid charging capabilities. Here's how we're revolutionizing your driving experience:</p>
            <ul>
              <li>
                Extended Range: Our state-of-the-art battery technology allows you to travel further on a single charge, reducing the need for frequent recharging stops. Whether you're commuting to work or embarking on a long-distance journey, Elextra's advanced batteries ensure you can reach your destination with ease.
              </li>
              <li>
                Faster Charging Times: We understand the importance of minimizing downtime. That's why our battery system is designed for ultra-fast charging, allowing you to get back on the road quicker than ever before. Our network of high-speed charging stations further enhances this convenience, making recharging as effortless as possible.
              </li>
              <li>
                Enhanced Efficiency: By optimizing energy consumption and storage, our batteries deliver superior performance and longevity. This means fewer replacements and a more sustainable driving experience.
              </li>
              <li>
                Safety and Reliability: Safety is paramount at Elextra Motors. Our batteries are rigorously tested to ensure they meet the highest safety standards, providing you with peace of mind on every journey.
              </li>
            </ul>
          </section>
          </section>
        </section>
        <!-- Activity 2 -->
        <section class="row">
          <section class="col-lg-5 py-5 bg-dark">
          <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
            <h2 class="display-4 m-0 h1">Autonomous Driving</h2>
          </section>
          </section>
          <section class="col-lg-7 p-0 hello">
          <section class="bg-light d-flex flex-column p-md-5 p-2">
            <h2 class="display-4">Activity 2</h2>
            <p class="lead">This is the secoaScript Summer Class.</p>
          </section>
          </section>
        </section>
        </section>
      </main>
      <footer class="">
        <section class="w-100 container pt-5 pb-3">
          <section class="d-flex flex-column flex-sm-row align-items-center justify-content-center">
            <section class="">
              <img style="min-width: 75px; max-width: 100px;" src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="Elxtra" class="w-100 d-inline-block align-text-top">
            </section>
            <section class="d-md-flex align-items-center m-auto my-3">
              <nav>
                <ul class="d-md-flex p-0 m-0">
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light active" aria-current="page" href="/">Home</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" href="#">About Us</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">Contact Us</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">FAQs</a>
                  </li>
                  <li class="nav-item">
                  <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">Car Models</a>
                  </li>
                </ul>
              </nav>
            </section>
            <section class="socials d-flex gap-3 align-items-center justify-content-center">
              <a href="#" class="text-light fs-4"><i class="fab fa-facebook"></i></a>
              <a href="#" class="text-light fs-4"><i class="fab fa-twitter"></i></a>
              <a href="#" class="text-light fs-4"><i class="fab fa-instagram"></i></a>
            </section>
          </section>
          <hr />
          <ul class="d-flex align-items-center justify-content-center gap-3 flex-wrap">
            <p class="m-3">© 2024 Elxtra. All rights reserved.</p>
            <li class="nav-item">
              <a class="nav-link p-0 m-3 text-light" href="#">Privacy Policy</a>
            </li>
            <li class="nav-item">
            <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">Terms and Conditions</a>
            </li>
            <li class="nav-item">
            <a class="nav-link p-0 m-3 text-light" href="#" tabindex="-1" aria-disabled="true">Cookie Policy</a>
            </li>
          </ul>
        </section>
      </footer>
      <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
      <script>
        const navbar = document.getElementById('navbar');

        window.addEventListener('resize', () => {
          if (window.innerWidth < 768) {
            navbar.classList.add('bg-dark');
          } else {
            navbar.classList.remove('bg-dark');
          }
        });

        window.addEventListener('scroll', () => {
          if (window.scrollY > 0) {
            navbar.classList.add('bg-dark');
            navbar.classList.add('border-darker');
          } else {
            navbar.classList.remove('bg-dark');
            navbar.classList.remove('border-darker');
          }
        });
      </script>
      <!-- Scroll Animation Script -->
      <script>
        let observer;
        function handleIntersect(entries, observer) {
          entries.forEach(entry => {
          if (entry.isIntersecting) {
            if (entry.target.dataset.animated !== 'true') {
            triggerAnimation(entry.target);
            entry.target.dataset.animated = 'true';
            }
          } else {
            entry.target.dataset.animated = 'false';
          }
          });
        }
      
        function triggerAnimation(element) {
          if (element.classList.contains('fade-down')) {
          element.classList.remove('fade-down');
          void element.offsetWidth;
          element.classList.add('fade-down');
          } else if (element.classList.contains('fade-right')) {
          element.classList.remove('fade-right');
          void element.offsetWidth;
          element.classList.add('fade-right');
          } else if (element.classList.contains('fade-left')) {
          element.classList.remove('fade-left');
          void element.offsetWidth;
          element.classList.add('fade-left');
          } else if (element.classList.contains('fade-up')) {
          element.classList.remove('fade-up');
          void element.offsetWidth;
          element.classList.add('fade-up');
          } else {
          element.classList.remove('fade');
          void element.offsetWidth;
          element.classList.add('fade');
          }
        }
      
        function setupIntersectionObserver() {
          const elements = document.querySelectorAll('.animate');
          const options = {
          root: null,
          rootMargin: '80px',
          threshold: 0.1
          };
      
          observer = new IntersectionObserver(handleIntersect, options);
      
          elements.forEach(element => {
          observer.observe(element);
          });
        }
        
        document.addEventListener('DOMContentLoaded', setupIntersectionObserver);
        </script>
      </body>
    </html>)";

      // Print the HTML code
      cout << htmlCode;

    return 0;
}