#include "window.h"

#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QStringList>
#include <QRegularExpression>
#include <QMap>
#include <QVector>
#include <algorithm>
#include <QFileDialog>
#include <QMessageBox>
#include <QIODevice>

Window::Window(QWidget *parent) :
   QWidget(parent)
{
   convert_button = new QPushButton("Convert", this);
   save_button = new QPushButton("Save Files", this);

   text_edit = new QTextEdit(this); 
   text_edit->setPlaceholderText("Text area");
   
   text_edited = new QTextEdit(this);
   text_edited->setPlaceholderText("Output area");
   text_edited->setReadOnly(true); 
   text_edited->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

   blacklist_edit = new QTextEdit(this);  
   blacklist_edit->setPlaceholderText("Enter blacklist words here (one per line)...");

   // Layout setup
   auto* layout = new QVBoxLayout(this);
   layout->addWidget(text_edit);
   layout->addWidget(blacklist_edit);
   layout->addWidget(convert_button);
   layout->addWidget(save_button); 
   layout->addWidget(text_edited);
   setLayout(layout);

   connect(convert_button, &QPushButton::clicked, this, [this](){
      QString userText = text_edit->toPlainText();   // Get text from input 
      QString blacklistText = blacklist_edit->toPlainText(); // Get blacklist words

      // Remove punctuation marks using a regular expression
      QString cleanedText = userText.remove(QRegularExpression("[.,!?;:\"'()\\[\\]{}<>]")); 

      QStringList words = userText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts); // Split into words

      // Process blacklist
      QStringList blacklistWords = blacklistText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

      // Convert blacklist to a set for fast lookup
      QSet<QString> blacklistSet = QSet<QString>(blacklistWords.begin(), blacklistWords.end());

      // Count occurrences of each word, excluding blacklisted words
      QMap<QString, int> wordCounts;
      for (const QString& word : words) {
         if (!blacklistSet.contains(word)) {
            wordCounts[word] += 1;
         }
      }
      // Convert QMap to QVector<QPair> for sorting
      QVector<QPair<QString, int>> sortedWords;
      for (auto it = wordCounts.cbegin(); it != wordCounts.cend(); ++it) {
         sortedWords.append(qMakePair(it.key(), it.value()));
      }

      // Sort words by their frequencies in descending order
      std::sort(sortedWords.begin(), sortedWords.end(), [](const QPair<QString, int>& a, const QPair<QString, int>& b) {
         return a.second > b.second;  // Sort by count, descending
      });


      // Format the output
      QString outputText;
      for (const auto& pair : sortedWords) {
         outputText += QString("%1 : %2\n").arg(pair.first).arg(pair.second);
      }

      text_edited->setText(outputText);                 // Set text in output 
   });

   connect(save_button, &QPushButton::clicked, this, [this]() {
      QString directory = QFileDialog::getExistingDirectory(this, "Select Folder to Save Files");
      if (!directory.isEmpty()) {
         // Save input text
         QString inputFilePath = QDir(directory).filePath("input.txt");
         QFile inputFile(inputFilePath);
         if (inputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&inputFile);
            out << text_edit->toPlainText();
            inputFile.close();
         }

         // Save blacklist
         QString blacklistFilePath = QDir(directory).filePath("blacklist.txt");
         QFile blacklistFile(blacklistFilePath);
         if (blacklistFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&blacklistFile);
            out << blacklist_edit->toPlainText();
            blacklistFile.close();
         }

         // Save output
         QString outputFilePath = QDir(directory).filePath("output.txt");
         QFile outputFile(outputFilePath);
         if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&outputFile);
            out << text_edited->toPlainText();
            outputFile.close();
         }

         QMessageBox::information(this, "Save Files", "Files have been saved successfully!");
      }
   });
}

