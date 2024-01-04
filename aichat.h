#ifndef AICHAT_H
#define AICHAT_H

#include <QWidget>

namespace Ui {
class AIChat;
}

class QNetworkAccessManager;
class QNetworkReply;

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

    /*!
     * \brief SetPropertiesButtonText Задать текст клавиши "Настройки" для перевода
     * \param buttonText Текст надписи
     */
    void SetPropertiesButtonText(const QString buttonText);

    /*!
     * \brief SetSendButtonText Задать текст клавиши "Отправить" для перевода
     * \param buttonText Текст надписи
     */
    void SetSendButtonText(const QString buttonText);

public slots:

    /*!
     * \brief SlotPropertiesButtonClicked Слот на клик клавиши "Настройки"
     */
    void SlotPropertiesButtonClicked();

    /*!
     * \brief SlotSendButtonClicked Слот на клик клавиши "Отправить"
     */
    void SlotSendButtonClicked();

    /*!
     * \brief SlotReceptionIsOver Слот на окончание передачи
     */
    void SlotReceptionFinished(QNetworkReply* );

private:
    Ui::AIChat *ui;         // Указатель на пользовательский интерфейс
    AIModels _currentLLM;   // Текущая языковая модель (LLM)
    QMap<AIModels, AIModelData> _mapModelsProperties;   // Свойства LLM
    QNetworkAccessManager* _pNetworkInterface;          // Указатель на объект сетевого интерфейса
};

#endif // AICHAT_H
