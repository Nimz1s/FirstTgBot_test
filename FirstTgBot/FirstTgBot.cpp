#include <stdio.h>
#include <tgbot/tgbot.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <curl/curl.h>

#include <algorithm>
#include <regex>
#include <filesystem>
#include <iostream>

#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>


#define SQLITECPP_COMPILE_DLL
#include <SQLiteCPP/SQLiteCpp.h>

#include "key.h"






SQLite::Database db("test.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
long messageId = -1;
int photoCounterInPull = 0;
int countOfnullsPhoto = 0;
char lastMode;



void firstMiniGame(const int64_t queryId, int messageId) {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    TgBot::Bot bot1("7513748253:AAFeoH9uDS-HR81BtjetPG5XzZq4l4EZadg");
    std::cout << "chat from Id" << queryId << std::endl;

    int znak = rand() % 4;
    int numbers = 1 + rand() % 2;

    char getZnak;
    switch (znak)
    {
    case 0:
        getZnak = '+';
        break;
    case 1:
        getZnak = '-';
        break;
    case 2:
        getZnak = '*';
        break;

    case 3:
        getZnak = '/';
        break;
    }

    int num1 = 0;
    int num2 = 0;
    int num3 = 0;

    switch (numbers)
    {
    case 1:
        num1 = rand() % 100;
        num2 = rand() % 10;
        break;
    case 2:
        num1 = rand() % 100;
        num2 = rand() % 10;
        break;
    case 3:
        num1 = rand() % 100;
        num2 = rand() % 10;
        break;
    }



    TgBot::InlineKeyboardMarkup::Ptr keyboardGame(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr Button1(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr Button2(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr Button3(new TgBot::InlineKeyboardButton);

    Button1->text = " ";
    Button2->text = " ";
    Button3->text = " ";
    Button1->callbackData = "Game";
    Button2->callbackData = "Game";
    Button3->callbackData = "Game";
    keyboardGame->inlineKeyboard.push_back({ Button1 });
    keyboardGame->inlineKeyboard.push_back({ Button2 });
    keyboardGame->inlineKeyboard.push_back({ Button3 });

    int result = 0;
    int fakeResult = 0;
    int position = rand() % 3;
    int fakeResult1, fakeResult2;

    switch (getZnak)
    {
    case '+':
    {
        try {
            result = num1 + num2;

            int fakeResult1, fakeResult2;
            fakeResult1 = result + (rand() % 10) + 1;
            fakeResult2 = result - (rand() % 10) + 1;

            switch (position)
            {
            case 0:
            {
                Button1->text = std::to_string(result);


                while (fakeResult1 == result || fakeResult2 == result)
                {
                    fakeResult1 = result + (rand() % 10) + 1;
                    fakeResult2 = result - (rand() % 10) + 1;
                }
                Button2->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);

                Button2->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";



            }
            break;
            case 1:
            {
                Button2->text = std::to_string(result);

                while (fakeResult1 == result || fakeResult2 == result)
                {
                    fakeResult1 = result + (rand() % 10) + 1;
                    fakeResult2 = result - (rand() % 10) + 1;
                }
                Button1->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);


                Button1->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";
            }
            break;
            case 2:
            {
                Button3->text = std::to_string(result);

                while (fakeResult1 == result || fakeResult2 == result)
                {
                    fakeResult1 = result + (rand() % 10) + 1;
                    fakeResult2 = result - (rand() % 10) + 1;
                }
                Button2->text = std::to_string(fakeResult1);
                Button1->text = std::to_string(fakeResult2);


                Button2->callbackData = "ENDgame";
                Button1->callbackData = "ENDgame";
            }
            break;
            default:
                break;
            }
            bot1.getApi().editMessageText(std::to_string(num1) + "+" + std::to_string(num2), queryId, messageId, "", "", false, keyboardGame);
        }
        catch (const std::exception& e) {
            bot1.getApi().sendMessage(messageId, "Не вдалося змінити повідомлення: " + std::string(e.what()));
        }
    }
    break;
    case '-':
    {
        try {

            result = num1 - num2;

            fakeResult1 = result + (rand() % 9);
            fakeResult2 = result - (rand() % 9);

            switch (position)
            {
            case 0:
            {
                Button1->text = std::to_string(result);



                while (fakeResult1 == result || fakeResult2 == result)
                {
                    fakeResult1 = result + (rand() % 9);
                    fakeResult2 = result - (rand() % 9);
                }
                Button2->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);


                Button2->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";



            }
            break;
            case 1:
            {
                Button2->text = std::to_string(result);


                while (fakeResult1 == result || fakeResult2 == result)
                {
                    fakeResult1 = result + (rand() % 9);
                    fakeResult2 = result - (rand() % 9);
                }
                Button1->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);

                Button1->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";

            }
            break;
            case 2:
            {
                Button3->text = std::to_string(result);


                while (fakeResult1 == result || fakeResult2 == result)
                {
                    fakeResult1 = result + (rand() % 9);
                    fakeResult2 = result - (rand() % 9);
                }
                Button2->text = std::to_string(fakeResult1);
                Button1->text = std::to_string(fakeResult2);

                Button2->callbackData = "ENDgame";
                Button1->callbackData = "ENDgame";

            }
            break;
            default:
                break;
            }
            bot1.getApi().editMessageText(std::to_string(num1) + "-" + std::to_string(num2), queryId, messageId, "", "", false, keyboardGame);
        }
        catch (const std::exception& e) {
            bot1.getApi().sendMessage(messageId, "Не вдалося змінити повідомлення: " + std::string(e.what()));
        }
    }
    break;
    case '*':
    {
        try {
            if (num1 == 0 || num2 == 0)
            {
                num1++;
                num2++;
            }
            result = num1 * num2;

            fakeResult1 = result + int(10 / (0.5 + double((rand() % 5 + 0.1) / 10)));
            fakeResult2 = result - int(10 / (0.5 + double((rand() % 5 + 0.1) / 10)));


            switch (position)
            {
            case 0:
            {
                Button1->text = std::to_string(result);


                Button2->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);

                Button2->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";


            }
            break;
            case 1:
            {
                Button2->text = std::to_string(result);


                Button1->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);

                Button1->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";

            }
            break;
            case 2:
            {
                Button3->text = std::to_string(result);


                Button2->text = std::to_string(fakeResult1);
                Button1->text = std::to_string(fakeResult2);

                Button2->callbackData = "ENDgame";
                Button1->callbackData = "ENDgame";

            }
            break;
            default:
                break;
            }
            bot1.getApi().editMessageText(std::to_string(num1) + "*" + std::to_string(num2), queryId, messageId, "", "", false, keyboardGame);
        }
        catch (const std::exception& e) {
            bot1.getApi().sendMessage(messageId, "Не вдалося змінити повідомлення: " + std::string(e.what()));
        }
    }
    break;
    case '/':
    {
        try {

            fakeResult1 = result + int(10 / (0.5 + double((rand() % 5 + 0.1) / 10)));
            fakeResult2 = result - int(10 / (0.5 + double((rand() % 5 + 0.1) / 10)));


            if (num1 == 0 || num2 == 0)
            {
                num1++;
                num2++;
            }
            if (num1 < num2)
            {
                int a = num1;
                num1 = num2;
                num2 = a;
            }
            while ((num1 % num2) != 0)
            {
                num1++;
            }
            result = num1 / num2;

            switch (position)
            {
            case 0:
            {
                Button1->text = std::to_string(result);


                Button2->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);

                Button2->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";



            }
            break;
            case 1:
            {
                Button2->text = std::to_string(result);


                Button1->text = std::to_string(fakeResult1);
                Button3->text = std::to_string(fakeResult2);

                Button1->callbackData = "ENDgame";
                Button3->callbackData = "ENDgame";

            }
            break;
            case 2:
            {
                Button3->text = std::to_string(result);


                Button2->text = std::to_string(fakeResult1);
                Button1->text = std::to_string(fakeResult2);

                Button2->callbackData = "ENDgame";
                Button1->callbackData = "ENDgame";
            }
            break;
            default:
                break;
            }
            bot1.getApi().editMessageText(std::to_string(num1) + "/" + std::to_string(num2), queryId, messageId, "", "", false, keyboardGame);
        }
        catch (const std::exception& e) {
            bot1.getApi().sendMessage(messageId, "Не вдалося змінити повідомлення: " + std::string(e.what()));
        }
    }
    break;
    }

    std::cout << "end func" << std::endl;
}


//////////////////////////////


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::ofstream* outFile = static_cast<std::ofstream*>(userp);
    outFile->write(static_cast<char*>(contents), totalSize);
    return totalSize;
}
// Функція для завантаження фото
void downloadPhoto(const std::string& fileId, TgBot::Bot& bot, const std::string& savePath) {
    // Отримуємо інформацію про фото через об'єкт бота
    TgBot::File::Ptr file = bot.getApi().getFile(fileId);  // Тепер ми використовуємо TgBot::File::Ptr
    std::string fileUrl = "https://api.telegram.org/file/bot" + bot.getToken() + "/" + file->filePath;  // Використовуємо "->" для доступу до властивостей

    // Завантажуємо фото
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        std::ofstream outFile(savePath, std::ios::binary);
        curl_easy_setopt(curl, CURLOPT_URL, fileUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();


    //if (isValidImageFormat(savePath)) {
    //    std::cout << "Фото збережено в " << savePath << std::endl;
    //}
    //else {
    //    std::cerr << "Невірний формат фото. Фото не збережено!" << std::endl;
    //    remove(savePath.c_str());  // Видаляємо файл, якщо формат неправильний
    //}
}
void pullOfNullPhoto(TgBot::Bot& bot, TgBot::Message::Ptr& message, char whatDo)
{
    TgBot::InlineKeyboardMarkup::Ptr keyboardPhoto(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr nextPhoto(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr previousPhoto(new TgBot::InlineKeyboardButton);

    keyboardPhoto->inlineKeyboard.clear();
    if (whatDo=='|' || whatDo == 'E')
    {
        lastMode = whatDo;
    }
    // Отримуємо кількість фото без імені
    countOfnullsPhoto = 0;
    if (lastMode =='|' || whatDo=='.')
    {
        SQLite::Statement getPhotoWithoutName2(db, "SELECT id FROM photo_info WHERE idTg = ? AND photoUserName IS NULL");
        getPhotoWithoutName2.bind(1, message->chat->id);
        while (getPhotoWithoutName2.executeStep()) {
            countOfnullsPhoto++;
        }
        std::cout << "countOfnullsPhoto (I): " << countOfnullsPhoto << std::endl;
    }
    else if (lastMode == 'E')
    {
        SQLite::Statement getPhotoWithName2(db, "SELECT id FROM photo_info WHERE idTg = ? AND photoUserName IS NOT NULL");
        getPhotoWithName2.bind(1, message->chat->id);
        while (getPhotoWithName2.executeStep()) {
            countOfnullsPhoto++;
        }
        std::cout << "countOfnullsPhoto (E): " << countOfnullsPhoto << std::endl;

    }
    else
    {

    }
    
    
    





    // Якщо whatDo == '.', виводимо тільки повідомлення з кнопкою "почати"
    if (whatDo == '.')
    {
        TgBot::InlineKeyboardButton::Ptr startButton(new TgBot::InlineKeyboardButton);
        TgBot::InlineKeyboardButton::Ptr EditNamePhoto(new TgBot::InlineKeyboardButton);

        startButton->text = "Почати перегляд фото у пуллі";
        startButton->callbackData = "startPhoto";
        EditNamePhoto->text = "Змінити назву фото";
        EditNamePhoto->callbackData = "EditNamePhoto";

        keyboardPhoto->inlineKeyboard.push_back({ startButton });
        keyboardPhoto->inlineKeyboard.push_back({ EditNamePhoto });

        bot.getApi().sendMessage(message->chat->id, "Натисніть кнопку, щоб почати перегляд фото", false, 0, keyboardPhoto);
        return; // Виходимо, не відправляючи фото
    }

    // Оновлюємо photoCounterInPull в залежності від напрямку
    if (whatDo == '|' || whatDo == 'E')
    {
        photoCounterInPull = photoCounterInPull;
    }
    else if (whatDo == '+')
    {
        if (photoCounterInPull + 2 <= countOfnullsPhoto)
        {
            photoCounterInPull += 2;  // рухаємось вперед
            whatDo = lastMode;
        }
        else
        {
            photoCounterInPull = photoCounterInPull + (countOfnullsPhoto % 2);  // максимальна кількість фото
            whatDo = lastMode;
        }
    }
    else if (whatDo == '-')
    {
        if (photoCounterInPull - 2 >= 0)
        {
            photoCounterInPull -= 2;  // рухаємось назад
            whatDo = lastMode;
        }
        else
        {
            photoCounterInPull = 0;  // мінімум 0
            whatDo = lastMode;
        }
    }


    int position = photoCounterInPull;
    if (whatDo == '|')
    {
        lastMode = '|';
        SQLite::Statement getPhotoWithoutName(db, "SELECT id FROM photo_info WHERE idTg = ? AND photoUserName IS NULL LIMIT 2 OFFSET ?");
        SQLite::Statement updateIdPhoto(db, "UPDATE photo_info SET messageIdTg = ? WHERE id = ?");
        getPhotoWithoutName.bind(1, message->chat->id);
        getPhotoWithoutName.bind(2, photoCounterInPull);
        int photoCount = 0;
        while (getPhotoWithoutName.executeStep())
        {
            std::string saveName = getPhotoWithoutName.getColumn(0).getString();
            std::string photoPath = "AllPhoto\\" + saveName + ".jpg";
            std::cout << "saveName: " << saveName << std::endl;

            // Відправляємо фото та зберігаємо messageId
            TgBot::Message::Ptr sentMsg = bot.getApi().sendPhoto(message->chat->id, TgBot::InputFile::fromFile(photoPath, "image/jpeg"));

            // Оновлюємо messageId для цього фото
            updateIdPhoto.bind(1, sentMsg->messageId);
            updateIdPhoto.bind(2, std::stoi(saveName));
            updateIdPhoto.exec();
            updateIdPhoto.reset();

            photoCount++;
        }
        position += photoCount;
    }
    else if (whatDo == 'E')
    {
        lastMode = 'E';
        SQLite::Statement getPhotoWithName(db, "SELECT id FROM photo_info WHERE idTg = ? AND photoUserName IS NOT NULL LIMIT 2 OFFSET ?");
        SQLite::Statement updateIdPhoto(db, "UPDATE photo_info SET messageIdTg = ? WHERE id = ?");
        getPhotoWithName.bind(1, message->chat->id);
        getPhotoWithName.bind(2, photoCounterInPull);
        int photoCount = 0;
        while (getPhotoWithName.executeStep())
        {
            std::string saveName = getPhotoWithName.getColumn(0).getString();
            std::string photoPath = "AllPhoto\\" + saveName + ".jpg";

            // Відправляємо фото та зберігаємо messageId
            TgBot::Message::Ptr sentMsg = bot.getApi().sendPhoto(message->chat->id, TgBot::InputFile::fromFile(photoPath, "image/jpeg"));

            // Оновлюємо messageId для цього фото
            updateIdPhoto.bind(1, sentMsg->messageId);
            updateIdPhoto.bind(2, std::stoi(saveName));
            updateIdPhoto.exec();
            updateIdPhoto.reset();

            photoCount++;
        }
        position += photoCount;
    }
    else if (whatDo == 'R')
    {
        SQLite::Statement updateIdPhoto(db, "UPDATE photo_info SET messageIdTg = ? WHERE id = ?");
        SQLite::Statement newestPhoto(db, "SELECT * FROM photo_info WHERE photoUserName = 'Розклад' ORDER BY createdAt DESC LIMIT 1");

        if (newestPhoto.executeStep()) {
            std::string id = newestPhoto.getColumn("id").getString();

            std::string photoPath = "AllPhoto\\" + id + ".jpg";

            // Відправляємо фото та зберігаємо messageId
            TgBot::Message::Ptr sentMsg = bot.getApi().sendPhoto(message->chat->id, TgBot::InputFile::fromFile(photoPath, "image/jpeg"));

            updateIdPhoto.bind(1, sentMsg->messageId);
            updateIdPhoto.bind(2, std::stoi(id));
            updateIdPhoto.exec();
        }
        else {
            bot.getApi().sendPhoto(message->chat->id, "Розкладу ще немає");
        }
    }

    // Вибір фото з бази даних на основі photoCounterInPull



    // Оновлення позиції після відправки фото

    // Логіка для кнопок
    if (countOfnullsPhoto == 0)
    {
        bot.getApi().sendMessage(message->chat->id, "Фото більше немає");
        return;

    }
    else if (countOfnullsPhoto == 1)
    {
        bot.getApi().sendMessage(message->chat->id, "Фотографії: " + std::to_string(position) + " з " + std::to_string(countOfnullsPhoto));
        return;
    }
    else if (photoCounterInPull == 0 && countOfnullsPhoto > 0)
    {
        keyboardPhoto->inlineKeyboard.clear();
        nextPhoto->text = "Наступні фото";
        nextPhoto->callbackData = "nextPhoto";
        keyboardPhoto->inlineKeyboard.push_back({ nextPhoto });
        bot.getApi().sendMessage(message->chat->id, "Фотографії: " + std::to_string(position) + " з " + std::to_string(countOfnullsPhoto), false, 0, keyboardPhoto);
        return;
    }
    else if (photoCounterInPull > 0 && photoCounterInPull < countOfnullsPhoto)
    {
        keyboardPhoto->inlineKeyboard.clear();
        nextPhoto->text = "Наступні фото";
        previousPhoto->text = "Минулі фото";
        nextPhoto->callbackData = "nextPhoto";
        previousPhoto->callbackData = "PreviousPhoto";

        keyboardPhoto->inlineKeyboard.push_back({ nextPhoto });
        keyboardPhoto->inlineKeyboard.push_back({ previousPhoto });
        bot.getApi().sendMessage(message->chat->id, "Фотографії: " + std::to_string(position) + " з " + std::to_string(countOfnullsPhoto), false, 0, keyboardPhoto);
        return;
    }
    else if (photoCounterInPull == countOfnullsPhoto)
    {
        keyboardPhoto->inlineKeyboard.clear();
        previousPhoto->text = "Минулі фото";
        previousPhoto->callbackData = "PreviousPhoto";
        keyboardPhoto->inlineKeyboard.push_back({ previousPhoto });
        bot.getApi().sendMessage(message->chat->id, "Фотографій більше немає, поверніться до фото наступною кнопкою:", false, 0, keyboardPhoto);
        return;

    }

    std::cout << "photoCounterInPull: " << photoCounterInPull << std::endl;
}


/////////////////////////////


struct FileInfo {
	int index; // Індекс файлу
    std::string name;
    /*std::string path;
    std::size_t size;*/
};

namespace fs = std::filesystem;
int extractNumber(const std::string& filename) {
    std::smatch match;
    std::regex pattern(R"(\b(\d+)\b)"); // Шукає перше число
    if (std::regex_search(filename, match, pattern)) {
        return std::stoi(match[1]);
    }
    return -1;
}
void allLabs(TgBot::Bot& bot, TgBot::Message::Ptr& message)
{
    

    TgBot::InlineKeyboardMarkup::Ptr allLabs(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr algoritms(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr arhitectura(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr kdm(new TgBot::InlineKeyboardButton);

    algoritms->text = "Алгоритми";
    algoritms->callbackData = "algoritms";

    arhitectura->text = "Архітектура";
    arhitectura->callbackData = "arhitectura";

    kdm->text = "КДМ";
    kdm->callbackData = "kdm";


    allLabs->inlineKeyboard.push_back({ algoritms });
    allLabs->inlineKeyboard.push_back({ arhitectura });
    allLabs->inlineKeyboard.push_back({ kdm });


    TgBot::Message::Ptr sentMessage = bot.getApi().sendMessage(message->chat->id, "Список з лабораторними: ", false, 0, allLabs);

    std::cout << sentMessage << std::endl;
    if (sentMessage) {
        messageId = sentMessage->messageId; // Перевірка, чи отримано messageId
        std::cout << messageId << std::endl;
    }
    bot.getApi().deleteMessage(message->chat->id, messageId - 1);
    

    return;
}
void outLabs(TgBot::Bot& bot, TgBot::Message::Ptr& message, std::string path)
{
    std::vector<FileInfo> files;

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                FileInfo fileInfo;
                fileInfo.name = entry.path().filename().string();
                files.push_back(fileInfo);
            }
        }

        // Натуральне сортування за номером лабораторної
        std::sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b) {
            return extractNumber(a.name) < extractNumber(b.name);
            });

        // Вивід
        std::string labs = "";
        int countLabs = 0;
        std::vector<FileInfo> lab;
        int itterator = 0;
        FileInfo fileInfo;
        for (const auto& file : files) {

            countLabs++;
        }
        for (const auto& file : files) {

            labs += file.name + "\n";
            
            fileInfo.index = itterator;  // Присвоюємо поточний індекс
            fileInfo.name = file.name;  // Присвоюємо ім'я файлу

            lab.push_back(fileInfo);  // Додаємо до вектора
            itterator++;

        }
        for (const auto& lab : lab) {
            std::cout << "Ітератор: " << lab.index << ", Назва: " << lab.name << std::endl;
        }

        bot.getApi().sendMessage(message->chat->id, labs);


		SQLite::Statement updateToFile(db, "UPDATE photo_info SET messageIdTg = ? WHERE idTg = ? AND messageIdTg = 0");
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }




    //std::string filePath = "D:/4NYHT/labs/algoritms/Алгоритми Лаба 1.txt";  // шлях до файлу
    //std::ifstream file(filePath, std::ios::binary);
    //if (!file.is_open()) {
    //    bot.getApi().sendMessage(message->chat->id, "Не вдалося відкрити файл.");
    //    return;
    //}

    //// Зчитування вмісту файлу у std::ostringstream
    //std::ostringstream oss;
    //oss << file.rdbuf();

    //// Підготовка InputFile
    //TgBot::InputFile::Ptr inputFile = std::make_shared<TgBot::InputFile>();
    //inputFile->data = oss.str();               // ✅ Тепер тип правильний: std::string
    //inputFile->fileName = "Алгоритми Лаба 1.txt";

    //bot.getApi().sendDocument(message->chat->id, inputFile);

    return;
}



int main() {

    TgBot::Bot bot(TG_BOT_KEY);


    db.exec("CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY UNIQUE, idTg INT, displayNikname TEXT, userNikname TEXT, password TEXT, isLoginedProcces INT, isLogined INT)");
    db.exec("CREATE TABLE IF NOT EXISTS leaderboard(id INTEGER PRIMARY KEY UNIQUE, idTg INT, score INT, maxScore INT)");
    db.exec("CREATE TABLE IF NOT EXISTS photo_info(id INTEGER PRIMARY KEY UNIQUE, idTg INT, photoNewName TEXT, photoUserName TEXT, messageIdTg INT DEFAULT 0, createdAt DATETIME DEFAULT CURRENT_TIMESTAMP)");




    try {
        // Встановлюємо команди меню
        std::vector<TgBot::BotCommand::Ptr> commands;

        TgBot::BotCommand::Ptr startCommand(new TgBot::BotCommand);
        startCommand->command = "start";
        startCommand->description = "Запустити бота";
        commands.push_back(startCommand);

        TgBot::BotCommand::Ptr sendPhoto(new TgBot::BotCommand);
        sendPhoto->command = "get_photo";
        sendPhoto->description = "Коледж";
        commands.push_back(sendPhoto);

        TgBot::BotCommand::Ptr Koledg(new TgBot::BotCommand);
        Koledg->command = "koledg";
        Koledg->description = "Відправити фото для збереження";
        commands.push_back(Koledg);
        



        bot.getApi().setMyCommands(commands); // Встановлення команд

        std::cout << "Меню команд встановлено успішно!" << std::endl;

    }
    catch (TgBot::TgException& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }






    TgBot::InlineKeyboardMarkup::Ptr keyboardMain(new TgBot::InlineKeyboardMarkup);
    bot.getEvents().onCommand("start", [&bot, keyboardMain](TgBot::Message::Ptr message) {

        keyboardMain->inlineKeyboard.clear();
        TgBot::InlineKeyboardButton::Ptr startGame(new TgBot::InlineKeyboardButton);
        TgBot::InlineKeyboardButton::Ptr leaders(new TgBot::InlineKeyboardButton);


        startGame->text = "Гра";
        leaders->text = "Таблиця лідерів";

        startGame->callbackData = "startGame";
        leaders->callbackData = "leaders";

        keyboardMain->inlineKeyboard.push_back({ leaders });
        keyboardMain->inlineKeyboard.push_back({ startGame });




        SQLite::Statement query(db, "SELECT COUNT(*) FROM users WHERE idTg = :userID");
        query.bind(":userID", message->chat->id); // Привязка значения к
        if (query.executeStep()) {
            int64_t count = query.getColumn(0).getInt();
            if (count > 0) {  // Пoлучение значения COUNT(*)
                std::cout << "ID" << message->chat->id << " found." << std::endl;
            }
            else {
                std::cout << "ID" << message->chat->id << " not found." << std::endl;
                // Добавляем данные
                SQLite::Statement query(db, "INSERT INTO users(idTg, displayNikname, isLoginedProcces, isLogined) VALUES(?, ?, ?, ?)");
                query.bind(1, message->chat->id);
                query.bind(2, "USER");
                query.bind(3, 0);
                query.bind(4, 0);
                try {
                    query.exec();
                }
                catch (const SQLite::Exception& e) {
                    std::cerr << "Помилка при виконанні SQL: " << e.what() << std::endl;
                }
            }
        }



        std::string userNikname;
        SQLite::Statement insertQuery(db, "SELECT displayNikname FROM users WHERE idTg = ?");
        insertQuery.bind(1, message->chat->id);
        if (insertQuery.executeStep()) {
            userNikname = insertQuery.getColumn(0).getString();
        }



        int isLogineds = 0;
        SQLite::Statement main(db, "SELECT isLogined FROM users WHERE idTg = ?");
        main.bind(1, message->chat->id);
        if (main.executeStep()) {
            isLogineds = main.getColumn(0).getInt();
        }
        if (isLogineds == 1)
        {
            TgBot::InlineKeyboardButton::Ptr Logout(new TgBot::InlineKeyboardButton);
            Logout->text = "Вийти з акаунта";
            Logout->callbackData = "Logout";
            keyboardMain->inlineKeyboard.push_back({ Logout });
        }
        else
        {

            TgBot::InlineKeyboardButton::Ptr buttonRegister(new TgBot::InlineKeyboardButton);
            TgBot::InlineKeyboardButton::Ptr buttonLogin(new TgBot::InlineKeyboardButton);


            buttonRegister->text = "Реєстрація";
            buttonRegister->callbackData = "Register";
            buttonLogin->text = "Логін";
            buttonLogin->callbackData = "Login";


            keyboardMain->inlineKeyboard.push_back({ buttonRegister });
            keyboardMain->inlineKeyboard.push_back({ buttonLogin });
        }




        bot.getApi().sendMessage(message->chat->id, "Вітаю, " + userNikname + "!", false, 0, keyboardMain);


        });

    
    bot.getEvents().onCommand("get_photo", [&bot](TgBot::Message::Ptr message) {
        SQLite::Statement startGetPhoto(db, "SELECT isLogined FROM users WHERE idTg = ?");
        startGetPhoto.bind(1, message->chat->id);

        bool isLogin;
        if (startGetPhoto.executeStep())
        {
            isLogin = startGetPhoto.getColumn(0).getInt();
        }
        std::cout << "isLogin" << isLogin << std::endl;
        if (isLogin)
        {
            char vuvid = '.';
            pullOfNullPhoto(bot, message, vuvid);
        }
        else
        {
            bot.getApi().sendMessage(message->chat->id, "Щоб мати доступ до функції потрібно бути зареєстрованим");
        }
        });

    TgBot::InlineKeyboardMarkup::Ptr keyboardKoledg(new TgBot::InlineKeyboardMarkup);
    bot.getEvents().onCommand("koledg", [&bot, keyboardKoledg](TgBot::Message::Ptr message) {
        TgBot::InlineKeyboardButton::Ptr KoledgDz(new TgBot::InlineKeyboardButton);
        TgBot::InlineKeyboardButton::Ptr KoledgLabu(new TgBot::InlineKeyboardButton);
        TgBot::InlineKeyboardButton::Ptr Rosklad(new TgBot::InlineKeyboardButton);


        Rosklad->text = "Розклад";
        Rosklad->callbackData = "getRosklad";


        KoledgLabu->callbackData = "Labu";
        KoledgLabu->text = "Лабораторні";

        KoledgDz->callbackData = "Dz";
        KoledgDz->text = "ДЗ";

        keyboardKoledg->inlineKeyboard.push_back({ KoledgLabu });
        keyboardKoledg->inlineKeyboard.push_back({ KoledgDz });
        keyboardKoledg->inlineKeyboard.push_back({ Rosklad });

        bot.getApi().sendMessage(message->chat->id, "Perevrka", false, 0, keyboardKoledg);


        });




    bot.getEvents().onCallbackQuery([&bot, &keyboardMain](TgBot::CallbackQuery::Ptr query) {
        if (query->data == "Register") {
            SQLite::Statement select(db, "SELECT isLogined FROM users WHERE idTg = ?");
            select.bind(1, query->from->id);
            int isLogined = 0; // Ініціалізація змінної

            if (select.executeStep()) {
                isLogined = select.getColumn(0).getInt();
            }

            if (isLogined == 1) {
                bot.getApi().sendMessage(query->from->id, "Ви уже увійшли в акаунт!");
            }
            else {
                SQLite::Statement registred(db, "UPDATE users SET isLoginedProcces = ? WHERE idTg = ?");
                registred.bind(1, 1);
                registred.bind(2, query->from->id);
                registred.exec();

                bot.getApi().sendMessage(query->message->chat->id, "Придумайте логін: ");
            }
        }
        else if (query->data == "Login") {
            SQLite::Statement login(db, "UPDATE users SET isLoginedProcces = ? WHERE idTg = ?");
            login.bind(1, 3);
            login.bind(2, query->from->id);
            login.exec();

            bot.getApi().sendMessage(query->message->chat->id, "Введіть ваш логін:");
        }
        else if (query->data == "Logout") {
            SQLite::Statement updateQuery(db, "UPDATE users SET displayNikname = ?, isLogined = ? WHERE idTg = ?");
            updateQuery.bind(1, "USER");
            updateQuery.bind(2, 0);
            updateQuery.bind(3, query->from->id);
            updateQuery.exec();

            bot.getApi().sendMessage(query->message->chat->id, "Ви вийшли з акаунта");
        }
        else if (query->data == "startGame") {
            TgBot::InlineKeyboardMarkup::Ptr keyboard1(new TgBot::InlineKeyboardMarkup);
            TgBot::InlineKeyboardButton::Ptr Button(new TgBot::InlineKeyboardButton);
            Button->text = "Почати";
            Button->callbackData = "Game";
            keyboard1->inlineKeyboard.push_back({ Button });


            TgBot::Message::Ptr sentMessage = bot.getApi().sendMessage(query->from->id, "Щоб почати гру натисніть кнопку", false, 0, keyboard1);

            std::cout << sentMessage << std::endl;
            if (sentMessage) {
                messageId = sentMessage->messageId; // Перевірка, чи отримано messageId
                std::cout << messageId << std::endl;
            }
            bot.getApi().deleteMessage(query->message->chat->id, messageId - 1);


            SQLite::Statement checkUser(db, "SELECT COUNT(*) FROM leaderboard WHERE idTg = ?");
            checkUser.bind(1, query->from->id);
            checkUser.executeStep();

            int userExists = checkUser.getColumn(0).getInt();  // 1 або 0

            if (userExists == 0) {
                // Якщо запису немає — додаємо нового користувача
                SQLite::Statement insertUser(db, "INSERT INTO leaderboard (idTg, score) VALUES (?, ?)");
                insertUser.bind(1, query->from->id);
                insertUser.bind(2, 0);
                insertUser.exec();
            }
            else {
                // Якщо запис є — оновлюємо score
                SQLite::Statement zeroScore(db, "UPDATE leaderboard SET score = ? WHERE idTg = ?");
                zeroScore.bind(1, 0);
                zeroScore.bind(2, query->from->id);
                zeroScore.exec();
            }

        }
        else if (query->data == "Game") {
            if (messageId == -1) { // Перевірка, чи є дійсний messageId
                bot.getApi().sendMessage(query->message->chat->id, "Помилка: не знайдено повідомлення для редагування. Натисніть 'Почати' ще раз.");
                return;
            }


            int score = 0;
            SQLite::Statement getScore(db, "SELECT score FROM leaderboard WHERE idTg = ?");
            getScore.bind(1, query->from->id);
            if (getScore.executeStep())
            {
                score = getScore.getColumn(0).getInt();
            }
            std::cout << "score is " << score << std::endl;

            if (query && query->message && query->message->chat) {

                firstMiniGame(query->from->id, messageId);
            }
            else {
                std::cerr << "Помилка: query, message або chat є nullptr!" << std::endl;
            }

            SQLite::Statement updateScore(db, "UPDATE leaderboard SET score = ? WHERE idTg = ?");
            updateScore.bind(1, ++score);
            updateScore.bind(2, query->from->id);
            updateScore.exec();

        }
        else if (query->data == "ENDgame")
        {



            bool isLogined = false;
            SQLite::Statement getLogin(db, "SELECT isLogined FROM users WHERE idTg = ?");
            getLogin.bind(1, query->from->id);
            if (getLogin.executeStep()) {
                isLogined = getLogin.getColumn(0).getInt();
            }



            if (isLogined)
            {

                SQLite::Statement getInfo(db, "SELECT * FROM leaderboard WHERE idTg = ?");
                getInfo.bind(1, query->from->id);
                int max = 0, newScore = 0;
                if (getInfo.executeStep()) {
                    newScore = getInfo.getColumn(2).getInt();
                    max = getInfo.getColumn(3).getInt();
                }

                if (max == 0)
                {
                    bot.getApi().editMessageText("Ви програли, ваш новий рекорд: " + std::to_string(newScore), query->message->chat->id, messageId);
                    SQLite::Statement updateScores(db, "UPDATE leaderboard SET score = ?, maxScore = ? WHERE idTg = ?");
                    updateScores.bind(1, 0);
                    updateScores.bind(2, newScore);
                    updateScores.bind(3, query->from->id);
                    updateScores.exec();
                }
                else if (newScore > max)
                {
                    bot.getApi().editMessageText("Ви побили свій рекорд! \n Ваш новий рекорд: " + std::to_string(newScore), query->message->chat->id, messageId);
                    SQLite::Statement updateScors(db, "UPDATE leaderboard SET score = ?, maxScore = ? WHERE idTg = ?");
                    updateScors.bind(1, 0);
                    updateScors.bind(2, newScore);
                    updateScors.bind(3, query->from->id);
                    updateScors.exec();
                }
                else
                {
                    bot.getApi().editMessageText("Ви не змогли побити всій минулий рекорд (" + std::to_string(max) +
                        ") \n Кількість балів у новій спробі: " + std::to_string(newScore), query->message->chat->id, messageId);
                    SQLite::Statement updateScore(db, "UPDATE leaderboard SET score = ? WHERE idTg = ?");
                    updateScore.bind(1, 0);
                    updateScore.bind(2, query->from->id);
                    updateScore.exec();
                }


            }
            else
            {
                bot.getApi().editMessageText("Oops, login to come in leaderboard", query->message->chat->id, messageId);

                SQLite::Statement updateScore(db, "UPDATE leaderboard SET score = ? WHERE idTg = ?");
                updateScore.bind(1, 0);
                updateScore.bind(2, query->from->id);
                updateScore.exec();
            }
        }
        else if (query->data == "leaders")
        {
            std::string leaderboardText = "🏆 Топ гравців:\n";
            SQLite::Statement getTopPlayers(db, "SELECT idTg, maxScore FROM leaderboard ORDER BY maxScore DESC LIMIT 5");

            int rank = 1;
            bool hasPlayers = false;  // Перевірка, чи є хоча б один запис

            while (getTopPlayers.executeStep()) {
                hasPlayers = true;
                int64_t userId = getTopPlayers.getColumn(0).getInt64();
                int userScore = getTopPlayers.getColumn(1).getInt();

                SQLite::Statement sel(db, "SELECT userNikname FROM users WHERE idTg = ?");
                sel.bind(1, userId);
                std::string displayNikname;

                if (sel.executeStep()) {
                    displayNikname = sel.getColumn(0).getString();
                }

                std::cout << "User ID: " << userId << ", Nikname: " << displayNikname << std::endl;

                leaderboardText += std::to_string(rank) + ". " + displayNikname + " - " + std::to_string(userScore) + " points\n";
                rank++;
            }

            // Якщо в базі немає записів
            if (!hasPlayers) {
                leaderboardText = "❌ У таблиці поки що немає гравців.";
            }

            // Надсилаємо повідомлення користувачеві
            bot.getApi().sendMessage(query->from->id, leaderboardText);
        }


        if (query->data == "startPhoto") {
            char vuvid = '|';  // Починаємо показ фото після натискання кнопки "Почати"
            pullOfNullPhoto(bot, query->message, vuvid);
        }
        else if (query->data == "nextPhoto") {
            char vuvid = '+';  // Перехід до наступних фото
            pullOfNullPhoto(bot, query->message, vuvid);
        }
        else if (query->data == "PreviousPhoto") {
            char vuvid = '-';  // Перехід до попередніх фото
            pullOfNullPhoto(bot, query->message, vuvid);
        }
        if (query->data == "EditNamePhoto") {
            SQLite::Statement editNamePhoto(db, "UPDATE users SET isLoginedProcces = ? WHERE idTg = ?");
			editNamePhoto.bind(1, 5);
			editNamePhoto.bind(2, query->from->id);
			editNamePhoto.exec();
			bot.getApi().sendMessage(query->message->chat->id, "Виберіть фото та введіть назву");

            char vuvid = 'E';
            pullOfNullPhoto(bot, query->message, vuvid);
        }

        else if (query->data == "getRosklad") {
			bot.getApi().sendMessage(query->message->chat->id, "Зарашній розклад: ");

            char vuvid = 'R';
            pullOfNullPhoto(bot, query->message, vuvid);
        }


        if (query->data == "Labu")
        {
            allLabs(bot, query->message);
        }
        if (query->data == "algoritms")
        {
            /*"D:/4NYHT/labs/архітектура"*/
            outLabs(bot, query->message, "D:/4NYHT/labs/algoritms");
        }

        });


    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        if (StringTools::startsWith(message->text, "/get_photo")) {
            return;
        }
        if (message->photo.size() > 0) {
            SQLite::Statement startGetPhoto(db, "SELECT isLogined FROM users WHERE idTg = ?");
            startGetPhoto.bind(1, message->chat->id);

            bool isLogin;
            if (startGetPhoto.executeStep())
            {
                isLogin = startGetPhoto.getColumn(0).getInt();
            }
            if (isLogin)
            {
                // Якщо є фото, беремо найкраще фото (найбільший розмір)
                TgBot::PhotoSize::Ptr bestPhoto = message->photo.back();
                std::string fileId = bestPhoto->fileId;


                SQLite::Statement selectPhoto(db, "SELECT id FROM photo_info ORDER BY id DESC LIMIT 1;");
                SQLite::Statement insertPhotoNextStep(db, "UPDATE photo_info SET photoNewName = ? WHERE id = ?");

                //якщо повідомлення надане з фото
                if (!message->caption.empty()) {
                    SQLite::Statement insertPhoto(db, "INSERT INTO photo_info (idTg, photoUserName, messageIdTg) VALUES (?, ?, ?)");
                    insertPhoto.bind(1, message->chat->id);
                    insertPhoto.bind(2, message->caption);
                    insertPhoto.bind(3, message->messageId);
                    insertPhoto.exec();

                    std::string saveName = " ";

                    if (selectPhoto.executeStep())
                        saveName = selectPhoto.getColumn(0).getString();

                    std::string savePath = "AllPhoto\\" + saveName + ".jpg";

                    insertPhotoNextStep.bind(1, savePath);
                    insertPhotoNextStep.bind(2, std::stoi(saveName));
                    insertPhotoNextStep.exec();

                    downloadPhoto(fileId, bot, savePath);
                    bot.getApi().sendMessage(message->chat->id, "Ваше фото збережено!");
                    
                }
                //якщо ні то зберігаємо в пул очікування
                else
                {
                    SQLite::Statement insertPhoto(db, "INSERT INTO photo_info (idTg, messageIdTg) VALUES (?, ?)");
                    insertPhoto.bind(1, message->chat->id);
                    insertPhoto.bind(2, message->messageId);
                    insertPhoto.exec();


                    std::string saveName = " ";
                    if (selectPhoto.executeStep())
                        saveName = selectPhoto.getColumn(0).getString();

                    std::string savePath = "AllPhoto\\" + saveName + ".jpg";
                    insertPhotoNextStep.bind(1, savePath);
                    insertPhotoNextStep.bind(2, std::stoi(saveName));
                    insertPhotoNextStep.exec();

                    downloadPhoto(fileId, bot, savePath);
                    bot.getApi().sendMessage(message->chat->id, "Ваше фото добавлено в пулл!");
                }
            }
            else
            {
                bot.getApi().sendMessage(message->chat->id, "Щоб мати доступ до функції потрібно бути зареєстрованим");
            }


            /*std::string name = "2323";

            std::string savePath = name+".jpg";*/
            /*downloadPhoto(fileId, bot, savePath);

            bot.getApi().sendMessage(message->chat->id, "Фото збережено в " + savePath);
            std::cout << "messageName " << messageName << std::endl;*/
            return;
        }

        int forSwitch = 0;
        if (message->replyToMessage != nullptr) {
            int repliedMessageId = message->replyToMessage->messageId;

            if (!message->replyToMessage->photo.empty()) {
                int haveText = 1;


                SQLite::Statement checkNull(db, "SELECT photoUserName FROM photo_info WHERE messageIdTg = ?");
                checkNull.bind(1, repliedMessageId);
                if (checkNull.executeStep())
                {
                    haveText = checkNull.getColumn(0).getBytes();
                }


                SQLite::Statement forSwitchs(db, "SELECT isLoginedProcces FROM users WHERE idTg = ?");
                forSwitchs.bind(1, message->chat->id);

                if (forSwitchs.executeStep()) {
                    forSwitch = forSwitchs.getColumn(0).getInt();
                }
                if (haveText == 0)
                {
                    SQLite::Statement updateUserNamePhoto(db, "UPDATE photo_info SET photoUserName = ? WHERE messageIdTg = ? ");
                    updateUserNamePhoto.bind(1, message->text);
                    updateUserNamePhoto.bind(2, std::to_string(message->replyToMessage->messageId));
                    updateUserNamePhoto.exec();
                    bot.getApi().sendMessage(message->chat->id, "Підпис для фото добавлено! ");
                    return;
                }
                else if (forSwitch == 5)
                {
                    SQLite::Statement updateUserNamePhoto(db, "UPDATE photo_info SET photoUserName = ? WHERE messageIdTg = ? ");
                    updateUserNamePhoto.bind(1, message->text);
                    updateUserNamePhoto.bind(2, std::to_string(message->replyToMessage->messageId));
                    updateUserNamePhoto.exec();
                    bot.getApi().sendMessage(message->chat->id, "Підпис для фото обновлено! ");

                    SQLite::Statement updateUserLogined(db, "UPDATE users SET isLoginedProcces = ? WHERE IdTg = ? ");
                    updateUserLogined.bind(1, 0);
					updateUserLogined.bind(2, message->chat->id);
					updateUserLogined.exec();

                    return;
                }
            }
        }



        
        SQLite::Statement forSwitchs(db, "SELECT isLoginedProcces FROM users WHERE idTg = ?");
        forSwitchs.bind(1, message->chat->id);

        if (forSwitchs.executeStep()) {
            forSwitch = forSwitchs.getColumn(0).getInt();
        }
        else {
            bot.getApi().sendMessage(message->chat->id, "Помилка отримання статусу користувача.");
            return;
        }

        switch (forSwitch) {
            // Користувач не зареєстрований
        case 0:
        {
            bot.getApi().sendMessage(message->chat->id, "Ваше повідомлення: " + message->text);
        }
        break;
        case 1:
        {
            SQLite::Statement checkQuery(db, "SELECT COUNT(*) FROM users WHERE displayNikname = ?");
            checkQuery.bind(1, message->text);  // Зв'язуємо значення імені

            int count;
            if (checkQuery.executeStep()) {
                count = checkQuery.getColumn(0).getInt();  // Отримуємо кількість знайдених записів
            }
            if (count > 0) {
                // Якщо ім'я вже існує, інформуємо користувача
                bot.getApi().sendMessage(message->chat->id, "Це ім'я вже зайняте, спробуйте інше.");
            }
            else
            {
                SQLite::Statement reg(db, "UPDATE users SET displayNikname = ?, userNikname = ?, isLoginedProcces = ? WHERE idTg = ?");
                reg.bind(1, message->text);
                reg.bind(2, message->text);
                reg.bind(3, 2);  // Тепер чекаємо пароль
                reg.bind(4, message->chat->id);
                reg.exec();
                bot.getApi().sendMessage(message->chat->id, "Придумайте пароль: ");
            }
        }
        break;
        case 2:
        {
            SQLite::Statement regs(db, "UPDATE users SET password = ?, isLoginedProcces = ?, isLogined = ? WHERE idTg = ?");
            regs.bind(1, message->text);
            regs.bind(2, 0);  // Завершення реєстрації
            regs.bind(3, 1);
            regs.bind(4, message->chat->id);
            regs.exec();
            bot.getApi().sendMessage(message->chat->id, "Реєстрація завершена!");
        }
        break;
        case 3:
        {
            SQLite::Statement checkQuery(db, "SELECT COUNT(*) FROM users WHERE userNikname = ?");
            checkQuery.bind(1, message->text);  // Зв'язуємо значення імені

            int count = 0;
            if (checkQuery.executeStep()) {
                count = checkQuery.getColumn(0).getInt();  // Отримуємо кількість знайдених записів
            }
            if (count == 0) {
                bot.getApi().sendMessage(message->chat->id, "Такого логіну не існує ❌");
                return;  // Вихід із функції, щоб уникнути подальших помилок
            }
            SQLite::Statement logLogin(db, "SELECT userNikname FROM users WHERE idTg = ?");
            logLogin.bind(1, message->chat->id);

            std::string checkNikname;
            if (logLogin.executeStep()) {
                checkNikname = logLogin.getColumn(0).getString();
            }


            if (checkNikname == message->text)
            {
                SQLite::Statement nextStep(db, "UPDATE users SET isLoginedProcces = ? WHERE idTg = ?");
                nextStep.bind(1, 4);
                nextStep.bind(2, message->chat->id);
                nextStep.exec();


                bot.getApi().sendMessage(message->chat->id, "Введіть пароль:");

            }
            else
            {
                bot.getApi().sendMessage(message->chat->id, "Неправильний логін!");
            }

        }
        break;
        case 4:
        {
            SQLite::Statement logPassword(db, "SELECT password FROM users WHERE idTg = ?");
            logPassword.bind(1, message->chat->id);

            std::string checkPassword;
            if (logPassword.executeStep())
            {
                checkPassword = logPassword.getColumn(0).getString();
            }

            if (checkPassword == message->text)
            {
                SQLite::Statement finalStep(db, "UPDATE users SET displayNikname = userNikname , isLoginedProcces = ?, isLogined = ? WHERE idTg = ?");
                finalStep.bind(1, 0);
                finalStep.bind(2, 1);
                finalStep.bind(3, message->chat->id);
                finalStep.exec();


                bot.getApi().sendMessage(message->chat->id, "Ви увійшли в акаунт!");

            }
            else
            {
                bot.getApi().sendMessage(message->chat->id, "Неправильний пароль!");
            }


        }
        break;

        //Залишити пустим для іншої роботи
        case 5:
        {
            
        }
        break;

        //Отримати фото ДЛЯ користувача
        case 6:
        {

        }
        break;

        default:  // Якщо значення для isLogined некоректне
            bot.getApi().sendMessage(message->chat->id, "Невідомий статус користувача.");
            break;
        }
        });




    try {
        bot.getApi().deleteWebhook();
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}