#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "user.h"
#include <vector>
#include <algorithm>
using namespace std;

class UserDatabase {
private:
    vector<User> users = {
        User(1, "John Yrrah Cabiles", "There is no absolute truth, only perspectives.", "Chief Executive Officer", "yrrahcc", "https://scontent.fmnl25-4.fna.fbcdn.net/v/t1.6435-9/129937480_3725664117526569_1060890035174470038_n.jpg?_nc_cat=109&ccb=1-7&_nc_sid=53a332&_nc_eui2=AeHz2cFeZLQiJWxT0OaJz9yZ3JlavkSgW8vcmVq-RKBby6eyvHWUW5RyrCFxHdi3jKJBPl6LF0WQnclATR5zdkzf&_nc_ohc=Ga6MoSRApgsQ7kNvgEvxqRR&_nc_ht=scontent.fmnl25-4.fna&oh=00_AYBJU-cbZhsf2EPLbS-skQ0xtwZw2_0rH0EZJCaWYMWZ4w&oe=66CAB06B", "jyrrahcc@gmail.com", "password123"),
        User(2, "Cedrick Libao", "Time is gold.", "Chief Marketing Officer","cedlib15", "https://scontent-mnl1-1.xx.fbcdn.net/v/t39.30808-6/221831942_1552136185132693_2448188182638511810_n.jpg?_nc_cat=101&ccb=1-7&_nc_sid=a5f93a&_nc_eui2=AeEn3e4E_ZfuuLlV-DtqHE0R_pLjpSd83W7-kuOlJ3zdbnpQLoygeWCXYLhXU60awXv1w08sw9JjfJyDq2FD7qb7&_nc_ohc=jZbkLdV6j2oQ7kNvgGZ49hf&_nc_ht=scontent-mnl1-1.xx&oh=00_AYC1JwwvCaX_YQzNT6A0HXwc1MwPtVgazdip1QdElzqlWw&oe=66A8349B", "cedricklibao@gmail.com", "password123"),
        User(3, "Hans Christian Purino", "When life gives you lemons, make lemonade.", "Chief Technology officer","hanspurr", "https://scontent-mnl1-1.xx.fbcdn.net/v/t39.30808-6/400685916_652746530371106_8942522707911560417_n.jpg?_nc_cat=105&ccb=1-7&_nc_sid=6ee11a&_nc_eui2=AeHNyYuEeXahxjCM4t3BEUl6zyGiujyJHcrPIaK6PIkdyqMEU_sT3RlpVr1Hjn03tE4nbdQqsTvnrFVGlHjAn4_j&_nc_ohc=qr00IQ3KvQwQ7kNvgEkrDm6&_nc_ht=scontent-mnl1-1.xx&oh=00_AYB4Q17fiTJiM2uMaAxlSO3KSJHph_LYAli0z4tCz-06cg&oe=66A839FD", "hcpurino@gmail.com", "password123"), 
        User(4, "John Paul Del Pilar", "Go beyond, Plus Ultra!", "Chief Operating Officer", "johnpdelp" , "https://scontent-mnl1-1.xx.fbcdn.net/v/t39.30808-6/371077123_279360344821347_6796263961140553935_n.jpg?_nc_cat=105&ccb=1-7&_nc_sid=6ee11a&_nc_eui2=AeHvbxdov0YL2VgT57SY_2uYUTUqRvW957NRNSpG9b3ns-1FoauiGl545QtI0YDvtoqmZthiSR8D37krhK5eufZM&_nc_ohc=cMLnBP9CTsIQ7kNvgEtwm12&_nc_ht=scontent-mnl1-1.xx&oh=00_AYBbuEzQ-CNjf4D-2v0DkOhDjvZhme1y9FIvbojvkAXl6Q&oe=66A8256B", "jpdelpilar@gmail.com", "password123"),
    };

public:
    // Default constructor
    UserDatabase() = default;

    // Constructor with initializer list
    UserDatabase(initializer_list<User> initialUsers) : users(initialUsers) {}

    // Add a user to the database
    void addUser(const User& user) {
        users.push_back(user);
    }

    // Remove a user from the database by ID
    void removeUser(int id) {
        users.erase(remove_if(users.begin(), users.end(), [id](const User& user) {
            return user.getId() == id;
        }), users.end());
    }

    // Update a user in the database
    User* getUserById(int id) {
        auto it = find_if(users.begin(), users.end(), [id](const User& user) {
            return user.getId() == id;
        });
        return it != users.end() ? &(*it) : nullptr;
    }

    // Get a user by username
    User* getUserByUsername(const string& username) {
        auto it = find_if(users.begin(), users.end(), [username](const User& user) {
            return user.getUserName() == username;
        });
        return it != users.end() ? &(*it) : nullptr;
    }

    // Get all users
    vector<User> getAllUsers() const {
        return users;
    }

    string displayAllUsers() const {
        std::string display = "";
        for (const User& user : users) {
            display += user.display();
        }
        return display;
    }

    // display user by username
    string displayUserByUsername(const string& username) {
        User* user = getUserByUsername(username);
        return user != nullptr ? user->display() : "User not found!";
    }
};

#endif // USERDATABASE_H