#include <stdio.h>
#include <tgbot/tgbot.h>
#include <string>

#define SQLITECPP_COMPILE_DLL
#include <SQLiteCPP/SQLiteCpp.h>






SQLite::Database db("test.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);






int main() {
    

    db.exec("CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY UNIQUE, idTg INT, userNikname TEXT, password TEXT, isLoginedProcces INT, isLogined INT)");


    /*SQLite::Statement select(db, "SELECT * FROM persons");
    while(select.executeStep())
    {
        std::cout << "Id: " << select.getColumn(0) << " Name: " << select.getColumn(1) << " Age: " << select.getColumn(2) << std::endl;
    }*/

    TgBot::InlineKeyboardMarkup::Ptr keyboardMain(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr buttonRegister(new TgBot::InlineKeyboardButton);
    TgBot::InlineKeyboardButton::Ptr buttonLogin(new TgBot::InlineKeyboardButton);


    buttonRegister->text = "Реєстрація";
    buttonRegister->callbackData = "Register";

    buttonLogin->text = "Логін";
    buttonLogin->callbackData = "Login";


    keyboardMain->inlineKeyboard.push_back({ buttonRegister });
    keyboardMain->inlineKeyboard.push_back({ buttonLogin });
    


    

    TgBot::Bot bot("7513748253:AAFeoH9uDS-HR81BtjetPG5XzZq4l4EZadg");
    bot.getEvents().onCommand("start", [&bot, keyboardMain](TgBot::Message::Ptr message) {
        
        


        SQLite::Statement query(db, "SELECT COUNT(*) FROM users WHERE idTg = :userID");
        query.bind(":userID", message->chat->id); // Привязка значения к
        if (query.executeStep()) {
            int count = query.getColumn(0).getInt();
            if (count > 0) {  // Пoлучение значения COUNT(*)
                std::cout << "ID" << message->chat->id << " found." << std::endl;
            }
            else {
                std::cout << "ID" << message->chat->id << " not found." << std::endl;
                // Добавляем данные
                SQLite::Statement query(db, "INSERT INTO users(idTg, userNikname, isLoginedProcces, isLogined) VALUES(?, ?, ?, ?)");
                query.bind(1, message->chat->id);
                query.bind(2, "USER");
                query.bind(3, 0);
                query.bind(4, 0);
                query.exec();
            }
        }



        std::string userNikname;
        SQLite::Statement insertQuery(db, "SELECT userNikname FROM users WHERE idTg = ?");
        insertQuery.bind(1, message->chat->id);
        if (insertQuery.executeStep()) {
            userNikname = insertQuery.getColumn(0).getString();
        }
        bot.getApi().sendMessage(message->from->id, "Вітаю, " + userNikname + "!", false, 0, keyboardMain);
    });


    bot.getEvents().onCallbackQuery([&bot, &keyboardMain](TgBot::CallbackQuery::Ptr query) {
        if (query->data == "Register") {

            SQLite::Statement select(db, "SELECT isLogined FROM users WHERE idTg = ?");
            select.bind(1, query->from->id);
            int isLogined ;
            if (select.executeStep()) {
                isLogined = select.getColumn(0).getInt();
                std::cout << "isLogined: " << isLogined << std::endl;
            } 
            else {
                std::cout << "Запит не знайшов жодного результату!" << std::endl;
            }

            std::cout << isLogined << query->from->id  << std::endl;
            if (isLogined == 1)
            {
                bot.getApi().sendMessage(query->from->id, "Ви уже увійшли в акаунт!");
            }
            else
            {
                SQLite::Statement registred(db, "UPDATE users SET isLoginedProcces = ? WHERE idTg = ?");
                registred.bind(1, 1);
                registred.bind(2, query->from->id);
                registred.exec();

                bot.getApi().sendMessage(query->from->id, "Придумайте логін: ");
            } 
        }
        else if (query->data == "Login")
        {

        }
        });


    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }

        int forSwitch = 0;
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
        case 0: // Користувач не зареєстрований
            bot.getApi().sendMessage(message->chat->id, "Ваше повідомлення: " + message->text);
            break;


        case 1:
        {
            SQLite::Statement checkQuery(db, "SELECT COUNT(*) FROM users WHERE userNikname = ?");
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
                SQLite::Statement reg(db, "UPDATE users SET userNikname = ?, isLoginedProcces = ? WHERE idTg = ?");
                reg.bind(1, message->text);
                reg.bind(2, 2);  // Тепер чекаємо пароль
                reg.bind(3, message->chat->id);
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


        default:  // Якщо значення для isLogined некоректне
            bot.getApi().sendMessage(message->chat->id, "Невідомий статус користувача.");
            break;
        }
        });




    try {
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