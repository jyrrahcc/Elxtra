#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
using namespace std;

class User {
private:
    int id;
    string name;
    string motto;
    string position;
    string userName;
    string pictureUrl;
    string email;
    string password;

public:
    User(int id, const string& name, const string& motto, const string& position, const string& userName, const string& pictureUrl, const string& email, const string& password)
        : id(id), name(name), motto(motto), position(position), userName(userName), pictureUrl(pictureUrl), email(email), password(password) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getMotto() const { return motto; }
    string getPosition() const { return position; }
    string getUserName() const { return userName; }
    string getPictureUrl() const { return pictureUrl; }
    string getEmail() const { return email; }
    string getPassword() const { return password; }

    void setName(const string& name) { this->name = name; }
    void setMotto(const string& motto) { this->motto = motto; }
    void setPosition(const string& position) { this->position = position; }
    void setUserName(const string& userName) { this->userName = userName; }
    void setPictureUrl(const string& pictureUrl) { this->pictureUrl = pictureUrl; }
    void setEmail(const string& email) { this->email = email; }
    void setPassword(const string& password) { this->password = password; }

    string display() const {
        return R"(<section class="container py-5 text-light d-flex align-items-center justify-content-center">
                <section class="row w-100">
                    <section class="col-md-4 text-center mt-5 d-flex flex-column align-items-center justify-content-center">
                        <img src=")" + getPictureUrl() + R"(" alt="User Image" class="border border-3 shadow border-light img-fluid rounded-circle mb-3">
                        <h2>)" + getUserName() + R"(</h2>
                        <p class="lead">)" + getEmail() + R"(</p>
                    </section>
                    <section class="col-md-8 d-flex align-items-center justify-content-center">
                        <section class="inset-card darkener p-4 rounded-3 row">
                            <section class="col-md-6">
                                <h2 class="fs-4">Profile Information</h2>
                                <div>
                                    <h3 class="mb-1 fs-6 fw-100">Name</h3>
                                    <p class="lead">)" + getName() + R"(</p>
                                </div>
                                <div>
                                    <h3 class="mb-1 fs-6 fw-100">Position</h3>
                                    <p class="lead">)" + getPosition() + R"(</p>
                                </div>
                                <div>
                                    <h3 class="mb-1 fs-6 fw-100">Motto</h3>
                                    <p class="lead">)" + getMotto() + R"(</p>
                                </div>

                            </section>
                            <section class="col-md-6">
                                <h2 class="fs-4">Account Information</h2>
                                <div class="form-floating mb-3 text-dark">
                                    <input type="text" class="form-control" id="username" name="username" placeholder="username" value=")" + getUserName() + R"(" readonly>
                                    <label class="text-dark" for="username">Username</label>
                                </div>
                                <div class="form-floating mb-3 text-dark">
                                    <input type="email" class="form-control" id="email" name="email" placeholder="email" value=")" + getEmail() + R"(" readonly>
                                    <label class="text-dark" for="email">Email</label>
                                </div>
                                <div class="form-floating mb-3 text-dark">
                                    <input type="password" class="form-control" id="password" name="password" placeholder="password" value=")" + getPassword() + R"(" readonly>
                                    <label class="text-dark" for="password">Password</label>
                                </div>
                            </section>
                        </section>
                    </section>
                </section>
            </section>)";
    }
};

#endif // USER_H