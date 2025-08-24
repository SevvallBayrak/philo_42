🍝 Philosophers Project  
---

## 🎯 Projenin Amacı  
Bu proje, bilgisayar bilimlerindeki klasik **Dining Philosophers** problemine dayanmaktadır.  
Amaç, filozofların **yemek yeme 🍴**, **uyuma 😴** ve **düşünme 💭** döngülerini **threads** ve **mutex** kullanarak simüle etmektir.  

Filozoflar yemek yiyebilmek için iki çatala ihtiyaç duyarlar. Çatallar paylaşıldığı için:  
- 🔒 **Senkronizasyon sorunları**  
- ⚠️ **Deadlock (kilitlenme) riskleri**  
ortaya çıkar.  
Bu projede hedef, bu sorunları çözüp filozofların **aç kalmadan** yaşam döngülerini sürdürmesini sağlamaktır.  

---

## 🧠 Neler Öğrendim?  
Bu proje sayesinde:  

- 🧵 **Thread** oluşturmayı ve yönetmeyi öğrendim.  
- 🔑 **Mutex** kullanarak **paylaşılan kaynakları güvenli şekilde kullanmayı** deneyimledim.  
- ⚡ **Race condition** ve 🛑 **Deadlock** kavramlarını öğrendim.  
- ⏱️ `gettimeofday` ve `usleep` ile **zaman yönetimini** nasıl yapacağımı kavradım.  
- ♻️ **Bellek yönetiminin** ne kadar önemli olduğunu fark ettim.  
- 💻 C dilinde **eşzamanlı programlamanın** temellerini keşfettim.  
