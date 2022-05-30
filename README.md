## MULTIPLATFORMSKA DETEKCIJA STROJNO ČITLJIVE ZONE NA OSOBNIM DOKUMENTIMA
***
### Diplomski rad

Autor: Saša Bajtl

Mentor: doc. dr. sc. Nikola Tanković

[Sveučilište Jurja Dobrile u Puli](https://www.unipu.hr/), [Fakultet informatike](https://fipu.unipu.hr/fipu)

### Sažetak
Tijekom posljednjih nekoliko godina, sve više se teži izradi aplikacija koje imaju jedan izvorišni kod, te isto tako po mogućnosti, taj isti kod da se optimalno izvršava na što više platformi. Razlog tome su troškovi koji mogu uslijediti kada bi za svaku platformu postojao jedan ili više programera. Da bi se to izbjeglo, danas se sve više aplikacija se pravi koje rade na svakom ili gotovo svakoj vrsti web preglednika, uz to da na aplikaciji radi jedna do nekoliko programera. Dakle za ovakav način izrade je potreban jedan tim stručnjaka, dok je nekad za svaku platformu bio potreban jedan stručnjaka. U tom slučaju riječ multiplatforma dolazi do izražaja.

Fokus ovog rada je na implementaciji jedne takve multiplatformske aplikacije čiji je izvorišni kod pisan u C++ koristeći OpenCV biblioteku računalnog vida, te se odnosi na multiplatformsku detekciju strojno čitljive zone na osobnim dokumentima. Osim C++ i OpenCv, za sustav izgradnje se koristi Shell skripte i Cmake sustav koji je odgovoran za automatsku izgradnju koda pokretanjem Shell skripti, od kojih je svaka skripta za izgradnju napisana za željenu platformu, u konkretnom slučaju desktop i web platformu, gdje za web platformu, glavnu ulogu igra Emscripten razvojni okvir, prevodeći izvorišni kod  u WebAssembly, predstavljajući sam pojam multiplatforme. Pored nabrojanih tehnologija, završnu riječ ima javascript preko kojeg se WebAssembly generiran kod koristi na web preglednicima. Rezultati rada objašnjavaju razlog zbog kojeg je ovakav način razvoja odličan, te uz neke od sitne nedostatke prilikom razvoja, u konačnici prevladavaju pozitivne strane ovakve vrste razvoja, od kojih je dokazana brzina izvođenja i stabilnost koja se može dovesti do zavidne razine.

### Opis sadržaja datoteka

DocumentExtractor --> Projektna datoteka

Dokumentacija: [priložena dokumentacija diplomskog rada](https://github.com/sbajtl/masters_thesis)

---------------------------------------------------------------------------------------

## MULTIPLATFORM DETECTION OF MACHINE READABLE ZONE ON PERSONAL DOCUMENTS
***
### Master's thesis

Author: Saša Bajtl

Mentor: doc. dr. sc. Nikola Tanković

[University of Jurja Dobrile of Pula](https://www.unipu.hr/), [Faculty of informatics](https://fipu.unipu.hr/fipu)

### Abstract
Over the last few years, there has been an increasing effort to build applications that have a single source code and, if possible, the same code to run optimally on as many platforms as possible. The reason for this is the cost that could follow if there were one or more developers for each platform. To avoid this, today more and more applications are being made that work on each or almost every type of web browser, with one to several developers working on the application. So this way of making requires one team of experts, while once one platform needed one expert. In this case, the word multiplatform comes to the fore.

This paper focuses on implementing one such multiplatform application whose source code is written in C ++ using the OpenCV computer vision library and refers to the multiplatform detection of the machine-readable zone on personal documents. In addition to C ++ and OpenCv, the construction system uses Shell scripts and the Cmake system, which is responsible for automatically building code by running Shell scripts, each of which is written for the desired platform, in this case, desktop and web platform, where for the web platform, the Emscripten development framework plays a major role, translating the source code into WebAssembly, representing the very concept of multiplatform. In addition to the listed technologies, the final word is javascript, through which WebAssembly generated code is used on web browsers. The results explain the reason why this method of development is excellent, and with some minor shortcomings in development, ultimately the positive aspects of this type of development prevail, of which proven speed and stability can be brought to an enviable level.

