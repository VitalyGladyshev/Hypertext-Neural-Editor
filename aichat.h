#ifndef AICHAT_H
#define AICHAT_H

#include <QWidget>

namespace Ui {
class AIChat;
}

/*!
 * \brief Перечисление AIModels - список моделей
 */
enum class AIModels
{
    GigaChat = 0,
    YandexGPT,
    ChatGPT,
    Llama
};

/*!
 * \brief Структура AIModelData - параметры языковых моделей
 */
struct AIModelData
{
    QString GetTokenPath;
};

/*!
 * \brief Класс AIChat ИИ чат
 */
class AIChat : public QWidget
{
    Q_OBJECT

public:
    /// Конструктор
    explicit AIChat(QWidget *parent = nullptr);
    /// Деструктор
    ~AIChat();

    // Задать текст клавиши "Настройки" для перевода
    void SetPropertiesButtonText(const QString buttonText);

    // Задать текст клавиши "Отправить" для перевода
    void SetSendButtonText(const QString buttonText);

private:
    Ui::AIChat *ui;         // Указатель на пользовательский интерфейс
    AIModels _currentLLM;   // Текущая языковая модель (LLM)
    QMap<AIModels, AIModelData> _mapModelsProperties;   // Свойства LLM
};

#endif // AICHAT_H
