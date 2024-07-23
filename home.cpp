#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    // Read the contents of the style sheet file
    ifstream styleSheetFile("./styles.css");
    string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
    styleSheetFile.close();

    cout << "Content-Type: text/html\n\n";

    // Generate the HTML code
    string htmlCode = R"(
    <!DOCTYPE html>
    <html lang="en">
      <head>
      <!-- Document Metadata -->
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
      <meta name="author" content="John Yrrah Cabiles">

      <!-- Favicon and Styles -->
      <link rel="icon" type="image/x-icon" href="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A">
      <style>)" + styleSheetContent + R"(</style>

      <!-- Bootstrap CSS -->
      <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
      <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" integrity="sha384-AYmEC3Yw5cVb3ZcuHtOA93w35dYTsvhLPVnYs9eStHfGJvOvKxVfELGroGkvsg+p" crossorigin="anonymous"/>

      <!-- Page Title -->
      <title>Car Enthusiasts</title>
      </head>
      <body>
      <!-- Navbar -->
      <header id="navbar" class="animate fixed-top navbar navbar-expand-md navbar-dark fade-down">
          <div class="container-fluid">
              <a class="navbar-brand d-flex gap-3 align-items-center" href="./index.cgi">
                   <img src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="" width="30" height="24" class="d-inline-block align-text-top">
                  <h1 class="display-4 fs-4 m-3">Car Enthusiasts</h1>
              </a>
            <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
              <span class="navbar-toggler-icon"></span>
            </button>
            <nav class="collapse navbar-collapse" id="navbarSupportedContent">
              <ul class="navbar-nav me-auto">
                <li class="nav-item">
                  <a class="nav-link p-0 m-3 active" aria-current="page" href="./home.cgi">Home</a>
                </li>
                <li class="nav-item">
                  <a class="nav-link p-0 m-3" href="./aboutus.cgi">About Us</a>
                </li>
                <li class="nav-item">
                  <a class="nav-link p-0 m-3" href="./contactus.cgi" tabindex="-1" aria-disabled="true">Contact Us</a>
                </li>
                <li class="nav-item">
                  <a class="nav-link p-0 m-3" href="./faqs.cgi" tabindex="-1" aria-disabled="true">FAQs</a>
                </li>
                <li class="nav-item">
                  <a class="nav-link p-0 m-3" href="./carmodels.cgi" tabindex="-1" aria-disabled="true">Car Models</a>
                </li>
              </ul>
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
                  <h2 class="display-3 text-light">Explore the World of Cars</h2>
                  <p class="lead text-light">Welcome to Car Enthusiasts, where we share the latest news, reviews, and insights about the automotive industry. Join us on a journey to discover the most exciting cars and innovations in the world of automobiles.</p>
                  <a href="#featured" class="btn btn-light text-danger fw-bold">Learn More</a>
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
          <h2><a href="#featured" class="text-light">Check Out Our Latest Articles</a></h2>
         </section>
        <!-- Featured Content -->
        <section id="featured" class="container-fluid">
        <section class="row">
          <section class="col-lg-5 py-5 bg-dark border-5 rounded-circle rounded-bottom border-light">
          <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
            <h2 class="display-4 m-0 h1">Latest Car Reviews</h2>
          </section>
          </section>
          <section class="col-lg-7 p-0 hello battery">
          <section class="h-100 d-flex flex-column p-md-5 p-2 text-light">
            <h2 class="display-4">In-Depth Reviews</h2>
            <p class="lead">Our team of experts brings you the latest reviews on new car models. From performance to design, we cover everything you need to know before making your next purchase.</p>
            <ul>
              <li>Detailed analysis of the latest car models.</li>
              <li>Comparisons between similar models to help you make an informed decision.</li>
              <li>Insights into the newest technologies and innovations in the automotive industry.</li>
            </ul>
          </section>
          </section>
        </section>
        <!-- Activity 2 -->
        <section class="row">
          <section class="col-lg-5 py-5 bg-dark">
          <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
            <h2 class="display-4 m-0 h1">Upcoming Events</h2>
          </section>
          </section>
          <section class="col-lg-7 p-0 hello battery">
          <section class="h-100 d-flex flex-column p-md-5 p-2 text-light">
            <h2 class="display-4">Stay Updated</h2>
            <p class="lead">Join us at the most exciting car events around the world. From auto shows to racing events, stay updated with our comprehensive event calendar.</p>
            <ul>
              <li>Upcoming auto shows and exhibitions.</li>
              <li>Racing events and competitions.</li>
              <li>Exclusive previews of new car models and technologies.</li>
            </ul>
          </section>
          </section>
        </section>
        <!-- Activity 3 -->
        <section class="row">
          <section class="col-lg-5 py-5 bg-dark">
          <section class="sticky-sm-top pos text-white text-center d-flex flex-column align-items-center justify-content-center">
            <h2 class="display-4 m-0 h1">Maintenance Tips</h2>
          </section>
          </section>
          <section class="col-lg-7 p-0 hello battery">
          <section class="h-100 d-flex flex-column p-md-5 p-2 text-light">
            <h2 class="display-4">Keep Your Car Running Smoothly</h2>
            <p class="lead">Get expert advice on how to maintain your car in top condition. From regular maintenance to troubleshooting common issues, our tips will help you keep your car running smoothly.</p>
            <ul>
              <li>Regular maintenance schedules.</li>
              <li>DIY tips for common car issues.</li>
              <li>Expert advice on car care and maintenance.</li>
            </ul>
          </section>
          </section>
        </section>
        </section>
      </main>
      <!-- Footer -->
      <footer id="footer" class="text-light">
        <section class="container py-5 d-flex flex-column align-items-center justify-content-center">
          <p>&copy; 2024 Car Enthusiasts. All rights reserved.</p>
        </section>
      </footer>
      <!-- Bootstrap JS -->
      <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXlL6bfgN+Fd3X0P3UHBdlE1Wus8n3hF0I9u1WjJs9ym/4B6V9IoP4yyCOWp" crossorigin="anonymous"></script>
      <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.min.js" integrity="sha384-cVKIPhG81rKXtW50b5BIe6mgjKK5Uhb6bU4lEN5Dzmc7z9z9Nf6lrlG1D8fU9w8L" crossorigin="anonymous"></script>
      </body>
    </html>
    )";

    cout << htmlCode;

    return 0;
}
