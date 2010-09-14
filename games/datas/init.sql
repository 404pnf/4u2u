use games;
DROP table user_words;
DROP table user_games;
DROP table user_awards;
CREATE TABLE user_words(user_id VARCHAR(30), words VARCHAR(60),weight INT);
CREATE TABLE user_games(user_id VARCHAR(30), user_name VARCHAR(30), game VARCHAR(20), level int, score int);
CREATE TABLE user_awards(user_id VARCHAR(30),user_name VARCHAR(30), send int,create_time TIMESTAMP); 