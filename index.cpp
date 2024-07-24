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
#include <unistd.h>
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

int main() {
    // Read the contents of the style sheet file
    ifstream styleSheetFile("./styles.css");
    string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
    styleSheetFile.close();

    cout << "Content-Type: text/html\n\n";

    string requestMethod = getenv("REQUEST_METHOD");
    // Read environment variables for cookie and query string
    string cookie_header = getenv("HTTP_COOKIE") ? getenv("HTTP_COOKIE") : "";
    map<string, string> cookies = parse_cookies(cookie_header);
    string name;
    // Check if the user is logged in
    if (requestMethod == "GET") {
      if (cookies.find("name") != cookies.end()) {
          name = cookies["name"];
      }
    }

    string userDisplay = "<div class=\"d-flex align-items-center text-light gap-3\">" + 
    (cookies.find("name") != cookies.end() ? 
          ("<div class='dropdown'>"
                "<button class='btn btn-outline-danger text-light fw-bold border-light dropdown-toggle' type='button' id='dropdownUser' data-bs-toggle='dropdown' aria-haspopup='true' aria-expanded='false'>" + 
                name +
                "</button>"
                "<div class='dropdown-menu dropdown-menu-end' aria-labelledby='dropdownUser'>"
                    "<a class='dropdown-item' href='./carloancalculator.cgi'>Car Loan Calculator</a>"
                    "<a class='dropdown-item' href='./userprofile.cgi'>User Profile</a>"
                    "<a class='dropdown-item' href='./logout.cgi'>Logout</a>"
                "</div>"
          "</div>") 
    : 
          "<a href='./login.cgi' class='btn btn-outline-danger text-light fw-bold border-light'>Login</a>") 
    + "</div>";

    string welcomeMessage = (cookies.find("name") != cookies.end() ? 
        ("<h2 class='display-3 text-light'>Welcome, " + name + "!</h2>") : 
        "<h2 class=\"display-3 text-light\">Drive the Future with Elxtra Motors</h2>");

        
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
      <!-- Navbar -->
      <header id="navbar" class="fixed-top header navbar navbar-expand-lg navbar-dark fade-down">
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
                    <a class="nav-link p-0 m-3 active" aria-current="page" href="./index.cgi">Home</a>
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
                <div class="d-flex justify-content-between align-items-center gap-3">
                <form method="post" action="./carmodels.cgi" class="form-inline flex-grow-1">
                    <section class="input-group">
                        <input class="form-control " type="search" placeholder="Search Car Model..." name="model" aria-label="Search" required>
                        <button class="btn btn-outline-danger border border-light text-light" type="submit"><i class="fas fa-search"></i></button>
                    </section>
                </form>)" + userDisplay + R"(</div></nav>
        </div>
      </header>
      <main>
        <!-- Hero Section -->
        <section class="min-vh-100 cover">
          <section class="darkener boundary py-5 w-100 d-flex align-items-center justify-content-center">
            <section class="container">
              <section class="row">
                <section class="col-sm-8 animate fade-left">
                  )" + welcomeMessage + R"(
                  <p class="lead text-light">At Elxtra Motors, we are redefining the automotive industry with our state-of-the-art electric vehicles. Our commitment to innovation and elegance sets us apart, offering you a driving experience like no other. Discover the future of transportation today with Elxtra.</p>
                  <a href="./aboutus.cgi" class="btn btn-light text-danger fw-bold">Learn More</a>
                </section>
                <section class="col-sm-4">
                </section>
              </section>
            </section>
          </section>
          <div class="arrow d-none d-sm-flex" onclick='window.scrollBy(50, window.innerHeight)'>
          </div>
        </section>
        <section class="bg-dark fade animate">
          <section class="container w-100 text-center overflow-hidden position-relative py-2 d-flex gap-5 align-items-center justify-content-center">
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
            <h2 class="h2 text-light m-auto">Elxtra</h2>
          </section>
        </section>
   <!-- Featured Content -->
     <section id="sticky-header" class="fade animate w-100 py-2 text-center border-top border-5 border-bottom border-light">
    <h2><a href="#featured" class="text-light">Check Out Our Latest Innovations</a></h2>
    </section>
<section id="featured" class="w-100 container-fluid">
  <section class="container-fuid">
  <section class="row">
    <section class="col-lg-5 py-5 bg-dark position-relative">
      <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
        <h2 class="display-4 m-0 h1">Advanced Battery System</h2>
      </section>
    </section>
    <section class="col-lg-7 p-0 hello battery" style="position: relative;">
      <form class="w-100 h-100 p-md-5 p-2 rounded shadow" style="background-color: rgba(50, 50, 50, 0.5); border: 1px solid #333; position: absolute; top: 0; left: 0;">
       <section class="mb-4 animate fade-right">
        <h2 class="display-3 text-light">Advanced Battery System</h2>
        <p class="lead text-light" style="font-size: 1.2rem;">At Elextra Motors, we are committed to pushing the boundaries of electric vehicle technology. Our latest battery system exemplifies this commitment by offering an impressive combination of extended range and rapid charging capabilities. Here's how we're revolutionizing your driving experience:</p>
        <ul class="list-unstyled">
          <li>
            <h3 class="h4 text-light">Extended Range:</h3>
            <p class="text-light" style="font-size: 1.1rem;">Our state-of-the-art battery technology allows you to travel further on a single charge, reducing the need for frequent recharging stops. Whether you're commuting to work or embarking on a long-distance journey, Elextra's advanced batteries ensure you can reach your destination with ease.</p>
          </li>
          <li>
            <h3 class="h4 text-light">Faster Charging Times:</h3>
            <p class="text-light" style="font-size: 1.1rem;">We understand the importance of minimizing downtime. That's why our battery system is designed for ultra-fast charging, allowing you to get back on the road quicker than ever before. Our network of high-speed charging stations further enhances this convenience, making recharging as effortless as possible.</p>
          </li>
          <li>
            <h3 class="h4 text-light">Enhanced Efficiency:</h3>
            <p class="text-light" style="font-size: 1.1rem;">By optimizing energy consumption and storage, our batteries deliver superior performance and longevity. This means fewer replacements and a more sustainable driving experience.</p>
          </li>
          <li>
            <h3 class="h4 text-light">Safety and Reliability:</h3>
            <p class="text-light" style="font-size: 1.1rem;">Safety is paramount at Elextra Motors. Our batteries are rigorously tested to ensure they meet the highest safety standards, providing you with peace of mind on every journey.</p>
          </li>
        </ul>
      </form>
    </section>
  </section>
</section>
  <!-- Autonomous Driving -->
 <section class="row">
  <section class="col-lg-5 py-5 bg-dark position-relative">
    <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
      <h2 class="display-4 m-0 h1">Autonomous Driving</h2>
    </section>
  </section>
  <section class="col-lg-7 p-0 hello autonomous" style="position: relative;">
    <form class="w-100 h-100 p-md-5 p-2 rounded shadow" style="background-color: rgba(50, 50, 50, 0.5); border: 1px solid #333; position: absolute; top: 0; left: 0;">
     <section class="mb-4 animate fade-right">
      <h2 class="display-3 text-light">Autonomous Driving</h2>
      <p class="lead text-light" style="font-size: 1.2rem;">At Elextra Motors, we are committed to revolutionizing the driving experience with our cutting-edge autonomous driving technology. Our system provides unparalleled convenience, safety, and efficiency. Here’s how we are transforming the future of driving:</p>
      <ul class="list-unstyled">
        <li>
          <h3 class="h4 text-light">Advanced Sensor Technology:</h3>
          <p class="text-light" style="font-size: 1.1rem;">Our autonomous driving system is equipped with state-of-the-art sensors that continuously monitor the vehicle’s surroundings, ensuring safe and accurate navigation under all conditions.</p>
        </li>
        <li>
          <h3 class="h4 text-light">Seamless Integration:</h3>
          <p class="text-light" style="font-size: 1.1rem;">The system integrates seamlessly with our vehicle’s existing technology, offering a smooth and intuitive user experience. Whether you're on the highway or in urban traffic, our autonomous driving technology adapts effortlessly to different driving environments.</p>
        </li>
        <li>
          <h3 class="h4 text-light">Enhanced Safety:</h3>
          <p class="text-light" style="font-size: 1.1rem;">Safety is our top priority. Our autonomous driving system is designed to respond to potential hazards in real-time, providing an additional layer of protection for you and your passengers.</p>
        </li>
        <li>
          <h3 class="h4 text-light">Improved Efficiency:</h3>
          <p class="text-light" style="font-size: 1.1rem;">By optimizing routes and driving patterns, our autonomous driving technology reduces energy consumption and enhances the overall efficiency of your journeys.</p>
        </li>
      </ul>
    </form>
  </section>
</section>
</section>

<!-- Smart Connectivity -->
    <section class="row">
      <section class="col-lg-5 py-5 bg-dark position-relative">
        <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
          <h2 class="display-4 m-0 h1">Smart Connectivity</h2>
        </section>
      </section>
      <section class="col-lg-7 p-0 hello smart" style="position: relative;">
        <form class="w-100 h-100 p-md-5 p-2 rounded shadow" style="background-color: rgba(50, 50, 50, 0.5); border: 1px solid #333; position: absolute; top: 0; left: 0;">
         <section class="mb-4 animate fade-right">
          <h2 class="display-3 text-light">Smart Connectivity</h2>
          <p class="lead text-light" style="font-size: 1.2rem;">At Elextra Motors, our vehicles are designed to keep you seamlessly connected, enhancing your driving experience with the latest in smart technology. Here’s how our smart connectivity features work:</p>
          <ul class="list-unstyled">
            <li>
              <h3 class="h4 text-light">Infotainment System:</h3>
              <p class="text-light" style="font-size: 1.1rem;">Our advanced infotainment system offers a wide range of entertainment options, navigation tools, and connectivity features, ensuring that you stay informed and entertained throughout your journey.</p>
            </li>
            <li>
              <h3 class="h4 text-light">Remote Monitoring:</h3>
              <p class="text-light" style="font-size: 1.1rem;">With our remote monitoring capabilities, you can check the status of your vehicle, including battery levels and maintenance alerts, from your smartphone or other connected devices.</p>
            </li>
            <li>
              <h3 class="h4 text-light">Voice Command:</h3>
              <p class="text-light" style="font-size: 1.1rem;">Our intuitive voice command system allows you to control various features of your vehicle without taking your hands off the wheel, providing a safer and more convenient driving experience.</p>
            </li>
            <li>
              <h3 class="h4 text-light">Wi-Fi Connectivity:</h3>
              <p class="text-light" style="font-size: 1.1rem;">Stay connected on the go with our built-in Wi-Fi, allowing you and your passengers to access the internet, stream media, and stay connected with the world, no matter where you are.</p>
            </li>
          </ul>
        </form>
      </section>
    </section>
  </section>
  </section>
</section>

  <!-- Customer Testimonials -->
  <section class="w-100 text-light">
    <section class="container py-5">
     <section class="mb-4 animate fade-lft">
        <h2 class="text-light text-center">Customer Testimonials</h2>
        <p class="lead text-light text-center">Read what our customers have to say about their experiences with Elxtra Motors</p>
        <section class="row d-flex align-items-center justify-content-center flex-wrap animate fade-up">
        <div class="row d-flex flex-wrap justify-content-center">
            <div class="col-lg-4 p-3">
                <section class="inset-card darkener d-flex flex-column align-items-left justify-content-center p-3 rounded-3">
                   <div class="stars" style="color: #ffdd57; margin-bottom: 20px;"> <!-- Increased margin-bottom for stars -->
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                    </div>
                    <p class="card-text">"Elxtra Motors has exceeded my expectations with their innovative electric vehicles."</p>
                    <div class="d-flex align-items-left">
                        <img src="https://expertphotography.b-cdn.net/wp-content/uploads/2019/02/Avoid-These-Stock-Images-5.jpg" alt="John Doe" class="rounded-circle mr-3" style="width: 50px; height: 50px; margin-right: 10px; margin-top: 5px;"> <!-- Added margin-right to the image -->
                        <div style="margin-top: 10px;"> <!-- Added margin-top to move this slightly below -->
                            <h5 class="card-title mb-0">John Doe</h5>
                            <p class="text-light small mb-0">CEO, ABC Company</p>
                        </div>
                    </div>
                </section>
            </div>
            <div class="col-lg-4 p-3">
                <section class="inset-card darkener d-flex flex-column align-items-left justify-content-center p-3 rounded-3">
                   <div class="stars" style="color: #ffdd57; margin-bottom: 20px;"> <!-- Increased margin-bottom for stars -->
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                    </div>
                    <p class="card-text">"I love driving my Elxtra electric car. It's stylish, eco-friendly, and a pleasure to drive."</p>
                    <div class="d-flex align-items-left">
                        <img src="https://img.freepik.com/premium-photo/asian-woman-standing-half-length-black-suit-businesswoman-holding-business-formal-suit-standing-office-room-concept-beautiful-confident-working-woman_102814-3676.jpg" alt="Jane Smith" class="rounded-circle mr-3" style="width: 50px; height: 50px; margin-right: 10px; margin-top: 5px;"> <!-- Added margin-right to the image -->
                        <div style="margin-top: 10px;"> <!-- Added margin-top to move this slightly below -->
                            <h5 class="card-title mb-0">Jane Smith</h5>
                            <p class="text-light small mb-0">Marketing Manager, XYZ Corp</p>
                        </div>
                    </div>
                </section>
            </div>
        <div class="col-lg-4 p-3">
                <section class="inset-card darkener d-flex flex-column align-items-left justify-content-center p-3 rounded-3">
                   <div class="stars" style="color: #ffdd57; margin-bottom: 20px;"> <!-- Increased margin-bottom for stars -->
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                        <i class="fas fa-star"></i>
                    </div>
                    <p class="card-text">"Switching to an Elxtra electric vehicle is efficient and cost-effective."</p>
                    <div class="d-flex align-items-left">
                        <img src="https://img.freepik.com/free-photo/portrait-serious-confident-male-office-worker-spectacles-formal-shirt-with-dark-skin-poses-spacious-cabinet_273609-3441.jpg" alt="Jane Smith" class="rounded-circle mr-3" style="width: 50px; height: 50px; margin-right: 10px; margin-top: 5px;"> <!-- Added margin-right to the image -->
                        <div style="margin-top: 10px;"> <!-- Added margin-top to move this slightly below -->
                            <h5 class="card-title mb-0">David Johnson</h5>
                            <p class="text-light small mb-0">CEO, 123 Industries</p>
                        </div>
                    </div>
                </section>
            </div>
        </div>
        </section>
    </section>
</section>
</section>

  <!-- Maintenance Services -->
<section class="w-100 text-light">
    <section class="container py-5">
        <section class="mb-4 animate fade-lft">
            <h2>Discover Our Range of Maintenance</h2>
            <h2>Services for Your Electric Vehicle</h2>
        </section>
        <div class="row d-flex flex-wrap justify-content-center">
           <section class="row d-flex flex-wrap animate fade-up">
            <div class="col-lg-4 p-3">
                <section class="inset-card darkener d-flex flex-column align-items-start  justify-content-center p-3 rounded-3" padding: 20px; border-radius: 10px;">
                    <img src="https://ideogram.ai/assets/image/lossless/response/jY_s02TgTQyIMFcAvLojNg" alt="Service 1" style="width: 100%; height: auto; margin-bottom: 10px;">
                    <h5 class="card-title mb-0 mt-3" style="font-size: 1.1rem; font-weight: bold;">Efficient Charging Solutions for Your Electric Vehicle</h5>
                    <p class="small mb-0 mt-3" style="font-size: 0.9rem;">Our team of experts is dedicated to providing top-notch customer support.</p>
                    <a href="#" style="margin-top: 10px; text-align: left; color:#c1bfc1;">Learn More ></a>
                </section>
            </div>
            <div class="col-lg-4 p-3">
                  <section class="inset-card darkener d-flex flex-column align-items-start  justify-content-center p-3 rounded-3" padding: 20px; border-radius: 10px;">
                    <img src="https://ideogram.ai/assets/progressive-image/balanced/response/PmHnbFWBRAC47pIMK7-XgA" alt="Service 2" style="width: 100%; height: auto; margin-bottom: 10px;">
                    <h5 class="card-title mb-0 mt-3" style="font-size: 1.1rem; font-weight: bold;">Enhance Your Electric Driving Experience with Our Services</h5>
                    <p class="small mb-0 mt-3" style="font-size: 0.9rem;">We offer a range of solutions to make your electric driving journey seamless.</p>
                     <a href="#" style="margin-top: 10px; text-align: left; color:#c1bfc1;">Discover ></a>
                </section>
            </div>
            <div class="col-lg-4 p-3">
                 <section class="inset-card darkener d-flex flex-column align-items-start  justify-content-center p-3 rounded-3" padding: 20px; border-radius: 10px;">
                    <img src="https://ideogram.ai/assets/image/lossless/response/MfJaa2DwQo6yiYnrk2PPOg" alt="Service 3" style="width: 100%; height: auto; margin-bottom: 10px;">
                    <h5 class="card-title mb-0 mt-3" style="font-size: 1.1rem; font-weight: bold;">Stay Connected with Our Customer Support Services</h5>
                    <p class="small mb-0 mt-3" style="font-size: 0.9rem;">Our customer support team is available to assist you whenever you need.</p>
                      <a href="./contactus.cgi" style="margin-top: 10px; text-align: left; color:#c1bfc1;">Contact ></a>
                </section>
            </div>
        </div>
    </section>
</section>
</section>

<!-- Call to action -->
<section class="w-100 text-light fade-up animate" style="background-image: url('https://ideogram.ai/assets/image/lossless/response/Fu1Y4up9Sreyx-tgdM7_9g'); background-size: cover; background-position: center;">
    <section class="darkener w-100">
    <section class="container py-5">
      <section>
        <h2 class="text-light">Experience the future of driving</h2>
        <p class="lead">Explore Our Models Now</p>
        <section class="d-flex">
            <a href='./carmodels.cgi' class='btn btn-outline-danger text-light fw-bold border-light'>Explore</a>
        </section>
      </section>
    </section>
    </section>
</section>
</section>
      </main>
      <!-- Footer Section -->
      <footer>
            <section class="w-100 container pt-5 pb-3">
                <section class="animate fade d-flex flex-column flex-sm-row align-items-center justify-content-center">
                    <section class="">
                        <img style="min-width: 75px; max-width: 100px;" src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="Elxtra" class="w-100 d-inline-block align-text-top">
                    </section>
                    <section class="d-md-flex align-items-center m-auto my-3">
                        <nav>
                            <ul class="d-md-flex p-0 m-0">
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./index.cgi">Home</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./aboutus.cgi">About Us</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./contactus.cgi">Contact Us</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./carmodels.cgi">Car Models</a>
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
                <hr class="animate fade" />
                <ul class="animate fade d-flex align-items-center justify-content-center gap-3 flex-wrap">
                    <p class="m-3">© 2024 Elxtra. All rights reserved.</p>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Privacy Policy</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Terms and Conditions</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Cookie Policy</a>
                    </li>
                </ul>
            </section>
        </footer>
      <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p" crossorigin="anonymous"></script>
      <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.min.js" integrity="sha384-cVKIPhGWiC2Al4u+LWgxfKTRIcfu0JTxR+EQDz/bgldoEyl4H0zUF0QKbrJ0EcQF" crossorigin="anonymous"></script>
      <script>
        const navbar = document.getElementById('navbar');

        window.addEventListener('resize', () => {
          if (window.innerWidth < 992) {
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
            if (window.innerWidth < 992) {
              navbar.classList.add('border-darker');
              navbar.classList.add('bg-dark');
            } else {
              navbar.classList.remove('border-darker');
              navbar.classList.remove('bg-dark');
            }
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