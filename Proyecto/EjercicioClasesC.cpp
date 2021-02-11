
// Librerías que contienen funciones estándar de C++
#include <iostream>
#include <cstdlib>
// Librería que contiene funciones matemáticas
#include <cmath>

// Librerías de OpenCV
// Se pueden cargar todas las Librerías incluyendo
//#include <opencv2/opencv.hpp>
// Contiene las definiciones fundamentales de las matrices e imágenes 
#include <opencv2/core/core.hpp> 
// Procesamiento de imágenes
#include <opencv2/imgproc/imgproc.hpp>
// Códecs de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp>
// Manejo de ventanas y eventos de ratón, teclado, etc.
#include <opencv2/highgui/highgui.hpp>
// Lectura de video
#include <opencv2/video/video.hpp>
// Escritura de video
#include <opencv2/videoio/videoio.hpp>

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV (Contiene funciones y definiciones de varios elementos de OpenCV)


int caculoGrisPromedio(Vec3b pixel3D) {
    return (pixel3D[0] + pixel3D[1] + pixel3D[2]) / 3;
}

int caculoGrisPonderado(Vec3b pixel3D) {
    return ((double)pixel3D[2]) * 0.3 + ((double)pixel3D[1]) * 0.59 + ((double)pixel3D[0]) * 0.11;
}

Mat convertirImgToGris(Mat imagen, int (*f)(Vec3b pixel3DParam)) {
    // Cómo clonar imágenes
    Mat imagenGris = Mat::zeros(Size(imagen.cols, imagen.rows), CV_8UC1);
    int pixel;
    for (int i = 0; i < imagen.rows; i++) {
        for (int j = 0; j < imagen.cols; j++) {
            // Calculo del pixel a escala de gris
            pixel = (*f)(imagen.at<Vec3b>(i, j));
            imagenGris.at<uchar>(i, j) = pixel;
        }
    }
    return imagenGris;
}

Mat calcularHistogramaManual(Mat imagenGris) {

    // Creamos una imagen llena de ceros que tenga el mismo tamaño de la imagen a color
    Mat imagenHist = Mat::zeros(Size(imagenGris.cols, imagenGris.rows), CV_8UC3); // Color

    // Cálculo del histograma
    int* histo = new int[256];

    for (int i = 0; i < 256; i++)
        histo[i] = 0;

    int pixel = 0;
    double maximo = -1;
    for (int i = 0; i < imagenGris.rows; i++) {
        for (int j = 0; j < imagenGris.cols; j++) {
            pixel = imagenGris.at<uchar>(i, j);
            histo[pixel]++;
        }
    }

    for (int i = 0; i < 256; i++) {
        if (histo[i] > maximo)
            maximo = histo[i];
    }

    for (int i = 0; i < 256; i++) {
        line(imagenHist, Point(i * 2, 373), Point(i * 2, 373 - (histo[i] * 373 / maximo)), Scalar(10, 200, 200), 2);
    }

    delete[] histo;
    return imagenHist;
}

Mat calcularHistogramaOpencv(Mat imagenGris) {

    // Divide la imagen en tres canales
        // vector<Mat> bgr_planes;
        // split(img, bgr_planes);
    Mat imagenHist = Mat::zeros(Size(imagenGris.cols, imagenGris.rows), CV_8UC3);

    // inicaliza las variables
    Mat histo;
    int histSize = 256;
    float range[] = { 0, histSize};
    const float* histRange = { range };

    // Calcula el histograma
    calcHist(&imagenGris, 1, 0, Mat(), histo, 1, &histSize, &histRange, true, false);
    double max_val = 0;
    minMaxLoc(histo, 0, &max_val);

    // genera la imagen
    for (int b = 0; b < histSize; b++) {
        float const binVal = histo.at<float>(b);
        int const height = cvRound(binVal * 350 / max_val);
        line(imagenHist, Point(b * 2, 350 - height), Point(b * 2 , 350), Scalar::all(255), 2);
    }

    return imagenHist;
}

void procesoCalcularHistogramas(Mat (*f)(Mat imagenGris)) {
    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png");
    cout << "Filas: " << imagen.rows << " Columnas: " << imagen.cols << " Canales: " << imagen.channels() << endl;
    resize(imagen, imagen, Size(), 0.5, 0.5); // cambia de tamaño

    // Convertimos las imagenes a escala de Gris
    Mat grisPromedio = convertirImgToGris(imagen, caculoGrisPromedio);
    Mat grisPonderado = convertirImgToGris(imagen, caculoGrisPonderado);

    // Calculamos los histogramas
    Mat histGrisPromedio = (*f)(grisPromedio);
    Mat histGrisPonderado = (*f)(grisPonderado);

    // Creamos una ventana donde se mostrará la imagen
    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("Gris Promedio", WINDOW_AUTOSIZE);
    namedWindow("Hist Promedio", WINDOW_AUTOSIZE);
    namedWindow("Gris Ponderado", WINDOW_AUTOSIZE);
    namedWindow("Hist Ponderado", WINDOW_AUTOSIZE);

    // Mostramos la imagen en pantalla
    imshow("Imagen", imagen);
    imshow("Gris Promedio", grisPromedio);
    imshow("Hist Promedio", histGrisPromedio);
    imshow("Gris Ponderado", grisPonderado);
    imshow("Hist Ponderado", histGrisPonderado);

    // Guardar las imagenes
    imwrite(".\\data\\Catedral-San-Basilio-Gris-Promedio.png", grisPromedio);
    imwrite(".\\data\\Catedral-San-Basilio-Gris-Ponderado.png", grisPonderado);
}

void procesoRestarImagenes() {
    // Lee las imagenes en escala de grises
    Mat img1 = imread(".\\data\\Imagen1.png", IMREAD_GRAYSCALE);
    Mat img2 = imread(".\\data\\Imagen2.png", IMREAD_GRAYSCALE);
    Mat imagenResta;

    // resta las imagenes
    absdiff(img1, img2, imagenResta);

    // muestra la imagen
    namedWindow("Imagen Resta", WINDOW_AUTOSIZE);
    imshow("Imagen Resta", imagenResta);
}

void procesoRestaImagenesVideo() {
    // Cómo manejar video
    //VideoCapture video("/dev/video33"); // si queremos poner el de la camara
    VideoCapture video(".\\data\\OneMinute.mkv");
    Mat anterior;
    Mat frameGris;
    Mat imagenResta;

    if (video.isOpened()) {
        Mat frame;
        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("Movimiento", WINDOW_AUTOSIZE);

        while (3 == 3) {
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);

            cvtColor(frame, frameGris, COLOR_BGR2GRAY);
            if (anterior.rows == 0 || anterior.cols == 0)
                anterior = frameGris.clone();

            absdiff(frameGris, anterior, imagenResta);
            anterior = frameGris.clone();

            if (frame.rows == 0 || frame.cols == 0)
                break;

            imshow("Video", frame);
            imshow("Movimiento", imagenResta);

            if (waitKey(23) == 27)
                break;

        }
    }
}

int k[2] = { 0, 0 }; // Representa el tamaño del kernel
Mat imagenSinFiltro;
Mat imagenMediana;
Mat imagenGaussiana;

void trackbarFiltroMediana(int v, void* p) {
    int* pX = (int*)p;
    cout << "Puntero: " << *pX << " -- " << "Valor: " << k[0] << endl;
    if (k[0] % 2 == 1) {
        medianBlur(imagenSinFiltro, imagenMediana, k[0]);
        imshow("MedianaBlur", imagenMediana);
    }
}

void trackbarFiltroGaussiana(int v, void* p) {
    int* pX = (int*)p;
    cout << "Puntero: " << *pX << " -- " << "Valor: " << k[1] << endl;
    if (k[1] % 2 == 1) {
        GaussianBlur(imagenSinFiltro, imagenGaussiana, Size(k[1], k[1]), 2, 2);
        imshow("GaussianBlur", imagenGaussiana);
    }
}

void procesoFiltrosMediaYGausiana(bool escalaGrises=false) {
    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    if (escalaGrises) {
        imagenSinFiltro = imread(".\\data\\Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    }else {
        imagenSinFiltro = imread(".\\data\\Catedral-San-Basilio.png");
    }
    resize(imagenSinFiltro, imagenSinFiltro, Size(), 0.5, 0.5);

    // muestra las imagenes
    namedWindow("MedianaBlur", WINDOW_AUTOSIZE);
    namedWindow("GaussianBlur", WINDOW_AUTOSIZE);
    // Muestra las imagenes
    imshow("MedianaBlur", imagenSinFiltro);
    imshow("GaussianBlur", imagenSinFiltro);

    // Agrega los trackbar
    int xM = 23, xG = 23;
    int *pXM = &xM, *pXG = &xG;
    createTrackbar("KernelM", "MedianaBlur", &k[0], 37, trackbarFiltroMediana, (void*) pXM);
    createTrackbar("KernelG", "GaussianBlur", &k[1], 37, trackbarFiltroGaussiana, (void*) pXG);

}

void procesoVideoEspacioDeColorHSV() {
    // VideoCapture video(0); // captura video de la camara
    VideoCapture video(".\\data\\OneMinute.mkv");

    if (video.isOpened()) {
        Mat frame;
        Mat frameHSV;

        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("HSV", WINDOW_AUTOSIZE);

        while (3 == 3) {
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            // Convierte a escala del color HSV
            cvtColor(frame, frameHSV, COLOR_BGR2HSV);

            imshow("Frame", frame);
            imshow("HSV", frameHSV);

            if (waitKey(23) == 27)
                break;
        }
    }

}

Mat filtroBordesSobel(Mat imagen) {
    // Inicializa los valores
    Mat gX;
    Mat gY;
    Mat gXAbs;
    Mat gYAbs;
    Mat sobelBordes;

    // Aplicamos el filto de sobel
    Sobel(imagen, gX, CV_16S, 1, 0);
    Sobel(imagen, gY, CV_16S, 0, 1);

    // Obtenemos los valores absolutos
    convertScaleAbs(gX, gXAbs);
    convertScaleAbs(gY, gYAbs);

    // Suma ponderada de 2 imágenes -> damos 50% a cada uno
    addWeighted(gXAbs, 0.5, gYAbs, 0.5, 0, sobelBordes);

    return sobelBordes;
}

Mat filtroBordesLaplace(Mat imagen) {
    Mat grisBlur;
    Mat bordesLaplace;
    Mat bordesLaplaceAbs;

    // Aplicamos el filto de laplace
    GaussianBlur(imagen, grisBlur, Size(3, 3), 0, 0);
    Laplacian(grisBlur, bordesLaplace, CV_16S, 3);

    // Obtenemos los valores absolutos
    convertScaleAbs(bordesLaplace, bordesLaplaceAbs);

    return bordesLaplaceAbs;
}

Mat filtroBordesCanny(Mat imagen, int umbral = 70, double ratio = 3.) {
    Mat grisBlur;
    Mat bordesCanny;

    // Aplicamos el filto de canny
    GaussianBlur(imagen, grisBlur, Size(3, 3), 0, 0);
    Canny(grisBlur, bordesCanny, umbral, umbral * ratio, 3);

    return bordesCanny;
}

void procesoDeteccionDeBordesSobel() {

    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    resize(imagen, imagen, Size(), 0.5, 0.5);

    // Detecta los bordes aplicando el fitro sobel
    Mat sobelBordes = filtroBordesSobel(imagen);

    // Mstramos las imganes
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Sobel", WINDOW_AUTOSIZE);
    imshow("Original", imagen);
    imshow("Sobel", sobelBordes);
}

void procesoDeteccionDeBordesLaplace() {

    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    resize(imagen, imagen, Size(), 0.5, 0.5);

    // Detecta los bordes aplicando el fitro lapalce
    Mat bordesLaplace = filtroBordesLaplace(imagen);

    // Mstramos las imganes
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Laplacian", WINDOW_AUTOSIZE);
    imshow("Original", imagen);
    imshow("Laplacian", bordesLaplace);
}

void procesoDeteccionDeBordesCanny() {
    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    resize(imagen, imagen, Size(), 0.5, 0.5);

    // Detecta los bordes aplicando el fitro canny
    Mat bordesCanny = filtroBordesCanny(imagen);

    // Mstramos las imganes
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Canny", WINDOW_AUTOSIZE);
    imshow("Original", imagen);
    imshow("Canny", bordesCanny);
}

void procesoDeteccionDeBordesVideo(int tipo=1) {
    VideoCapture video(0);
    if (video.isOpened()) {
        Mat frame;
        Mat imagenGris;
        Mat imagenBorde;

        string titulo = tipo == 2 ? "Laplace": tipo == 3 ? "Candy" : "Sobel";
        namedWindow("Camara", WINDOW_AUTOSIZE);
        namedWindow("Img Borde " + titulo, WINDOW_AUTOSIZE);

        while (3 == 3) {
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            cvtColor(frame, imagenGris, COLOR_BGR2GRAY);
            switch (tipo) {
                case 2:
                    imagenBorde = filtroBordesLaplace(imagenGris);
                break;
                case 3:
                    imagenBorde =  filtroBordesCanny(imagenGris);
                break;
                default:
                    imagenBorde = filtroBordesSobel(imagenGris);
            }
            // muestra la imagen
            imshow("Camara", frame);
            imshow("Img Borde " + titulo, imagenBorde);

            if (waitKey(23) == 27)
                break;
        }
    }
}

void procesoRuidoSalPimienta(bool esSal = true) {
    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    resize(imagen, imagen, Size(), 0.5, 0.5);
    Mat imagenRuidoSal = imagen.clone();

    // Aplicamos el ruido
    int total = (int)(0.2 * imagenRuidoSal.rows * imagenRuidoSal.cols);
    cout << "Total: " << total << endl;
    int cont = 0, fila = 0, col = 0;

    srand(time(0));
    while (cont < total) {
        fila = rand() % imagenRuidoSal.rows;
        col = rand() % imagenRuidoSal.cols;
        cont++;
        imagenRuidoSal.at<uchar>(fila, col) = esSal? 255: 0;
    }

    // Mstramos las imganes
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("RuidoSalPimienta", WINDOW_AUTOSIZE);
    imshow("Original", imagen);
    imshow("RuidoSalPimienta", imagenRuidoSal);
}

Mat imagenSinUmbral;
Mat imgenConUmbral;
int umbral = 255;
int minH = 19, minS = 30, minV = 183;
int maxH = 44, maxS = 255, maxV = 255;

void trackBarEventGris(int v, void* p) {
    threshold(imagenSinUmbral, imgenConUmbral, umbral, 255, THRESH_BINARY);
    imshow("Threshold", imgenConUmbral);
}

void procesoUmbralizacionGris() {
    // Leemos la imagen y la guardamos en una matriz llamada "imagen"
    imagenSinUmbral = imread(".\\data\\Catedral-San-Basilio.png", IMREAD_GRAYSCALE);
    resize(imagenSinUmbral, imagenSinUmbral, Size(), 0.7, 0.7);

    threshold(imagenSinUmbral, imgenConUmbral, umbral, 255, THRESH_BINARY);

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Threshold", WINDOW_AUTOSIZE);

    createTrackbar("Threshold", "Original", &umbral, 255, trackBarEventGris, NULL);

    imshow("Original", imagenSinUmbral);
    imshow("Threshold", imgenConUmbral);
}

void procesoUmbralizacionHSV() {
    VideoCapture video(0);

    if (video.isOpened()) {
        Mat frame;
        Mat imgenHSV;
        Mat roi; // Region of Interes, Zona de Interés

        Mat objeto;

        namedWindow("Frame", WINDOW_AUTOSIZE);
        namedWindow("HSV", WINDOW_AUTOSIZE);
        namedWindow("ROI", WINDOW_AUTOSIZE);
        namedWindow("Objeto", WINDOW_AUTOSIZE);

        createTrackbar("H-Min", "Frame", &minH, 180);
        createTrackbar("S-Min", "Frame", &minS, 255);
        createTrackbar("V-Min", "Frame", &minV, 255);

        createTrackbar("H-Max", "Frame", &maxH, 180);
        createTrackbar("S-Max", "Frame", &maxS, 255);
        createTrackbar("V-Max", "Frame", &maxV, 255);

        int pixel = 0;

        while (3 == 3) {
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            cvtColor(frame, imgenHSV, COLOR_BGR2HSV);
            inRange(imgenHSV, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), roi);

            objeto = Mat(Size(frame.cols, frame.rows), CV_8UC3, Scalar(255, 255, 255));
            for (int i = 0; i < roi.rows; i++) {
                for (int j = 0; j < roi.cols; j++) {
                    pixel = roi.at<uchar>(i, j);
                    if (pixel > 0) {
                        objeto.at<Vec3b>(i, j) = frame.at<Vec3b>(i, j);
                    }
                }
            }

            imshow("Frame", frame);
            imshow("HSV", imgenHSV);
            imshow("ROI", roi);
            imshow("Objeto", objeto);

            if (waitKey(23) == 27)
                break;
        }
    }
}

void procesoCortarTriangulo() {
    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png");
    resize(imagen, imagen, Size(), 0.5, 0.5);
    Mat imagenF = imagen.clone();
    line(imagenF, Point(130, 180), Point(50, 280), Scalar(0, 0, 0));
    line(imagenF, Point(50, 280), Point(240, 310), Scalar(0, 0, 0));
    line(imagenF, Point(240, 310), Point(130, 180), Scalar(0, 0, 0));
    // circle(imagenF, Point(80, 180), 40, Scalar(0, 0, 0));

    Mat imagenR;
    Mat imagenR1 = imagen.clone();
    absdiff(imagen, imagenF, imagenR);
    cvtColor(imagenR, imagenR, COLOR_BGR2GRAY);

    bool esTramo = false;
    int pixel, tramoI, tramoF;
    for (int i = 0; i < imagenR.rows; i++)
    {
        for (int j = 0; j < imagenR.cols; j++)
        {
            pixel = imagenR.at<uchar>(i, j);
            if (esTramo) {
                if (pixel > 0) {
                    if (j - tramoI > 1) {
                        tramoF = j;
                        esTramo = false;
                        for (int k = tramoI; k < tramoF; k++)
                        {
                            imagenR1.at<Vec3b>(i, k) = Vec3b(255, 255, 255);
                        }
                    }
                    else {
                        tramoI = j;
                        imagenR1.at<Vec3b>(i, tramoI) = Vec3b(255, 255, 255);
                    }
                   
                }
            }
            else {
                if (pixel > 0) {
                    tramoI = j;
                    esTramo = true;
                    imagenR1.at<Vec3b>(i, tramoI) = Vec3b(255, 255, 255);
                }
            }
        }
        esTramo = false;
    }
    // Quita los pixeles de ese triangulo
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Copia con triangulo", WINDOW_AUTOSIZE);
    namedWindow("Resta", WINDOW_AUTOSIZE);
    imshow("Original", imagen);
    imshow("Copia con triangulo", imagenF);
    imshow("Resta", imagenR1);

}

void procesoCortarFuncionSeno() {
    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png");
    resize(imagen, imagen, Size(), 0.5, 0.5);
    Mat imagenR = imagen.clone();
    double y, mitad = imagenR.rows / 2;
    for (double x = 0.0; x < imagenR.cols; x += 0.08)
    {
        y = mitad - (sin(x * 0.06) * 15);
        line(imagenR, Point(x, y), Point(x, imagenR.rows), Scalar(0));
    }
    // mostramos las imagenes
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Seno", WINDOW_AUTOSIZE);
    imshow("Original", imagen);
    imshow("Seno", imagenR);
}

void procesoCortarTriangulo2() {

    Mat imagen = imread(".\\data\\Catedral-San-Basilio.png");
    Mat imagenT = imagen.clone();
    line(imagenT, Point(130, 180), Point(50, 280), Scalar(0, 0, 0));
    line(imagenT, Point(50, 280), Point(240, 310), Scalar(0, 0, 0));
    line(imagenT, Point(240, 310), Point(130, 180), Scalar(0, 0, 0));
    circle(imagenT, Point(80, 180), 40, Scalar(0, 0, 0));
    Mat imgRojo;

    Mat resta = abs(imagen - imagenT);
    Mat destino = Mat(Size(imagen.cols, imagen.rows), CV_8UC3, Scalar(255, 255, 255));
    imgRojo = Mat(Size(destino.cols, destino.rows), CV_8UC3, Scalar(0, 0, 0));

    Vec3b pixel;
    Vec3b pixelR;
    Vec3b pixelCopia;

    for (int i = 0; i < imagen.rows; i++) {
        for (int j = 0; j < imagen.cols; j++) {
            pixel = resta.at<Vec3b>(i, j);
            if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) {
                pixelCopia = imagen.at<Vec3b>(i, j);
                destino.at<Vec3b>(i, j) = pixelCopia;
            }
            else {
                break;
            }
        }

        for (int j = imagen.cols - 1; j > 0; j--) {
            pixelR = resta.at<Vec3b>(i, j);
            if (pixelR[0] == 0 && pixelR[1] == 0 && pixelR[2] == 0) {
                pixelCopia = imagen.at<Vec3b>(i, j);
                destino.at<Vec3b>(i, j) = pixelCopia;
            }
            else
                break;
        }

    }

   
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Resta", WINDOW_AUTOSIZE);
    namedWindow("Triangulo", WINDOW_AUTOSIZE);
    namedWindow("Destino", WINDOW_AUTOSIZE);
    //namedWindow("Rojo", WINDOW_AUTOSIZE);

    imshow("Original", imagen);
    imshow("Resta", resta);
    imshow("Triangulo", imagenT);
    imshow("Destino", destino);
    //imshow("Rojo", imgRojo);

}

void procesoCompletarCirculo() {
    Mat imagenOriginal = imread("MOROCHO_MEDINA_CARLOS_HOMERO-1.png");
    Mat imagenAlterada = imread("MOROCHO_MEDINA_CARLOS_HOMERO-2.png");
    Mat imagenResultado = imagenOriginal.clone();

    Vec3b pixel;
    for (int i = 0; i < imagenOriginal.rows; i++)
    {
        for (int j = 0; j < imagenOriginal.cols; j++)
        {
            pixel = imagenOriginal.at<Vec3b>(i, j);
            if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) {
                imagenResultado.at<Vec3b>(i, j) = imagenAlterada.at<Vec3b>(i, j);
            }
        }
    }

    // Agrego las ventanas
    namedWindow("Imagen Original", WINDOW_AUTOSIZE);
    namedWindow("Imagen Alterada", WINDOW_AUTOSIZE);
    namedWindow("Imagen Resultado", WINDOW_AUTOSIZE);
    
    // Muestro las imagenes
    imshow("Imagen Original", imagenOriginal);
    imshow("Imagen Alterada", imagenAlterada);
    imshow("Imagen Resultado", imagenResultado);

    // Guardo la immagen
    imwrite("Imagen-Resultado-CM.png", imagenResultado);

}


int main(int argc, char* argv[]) {
    // En OpenCV las imágenes a color se representan como BGR:
   
    //// llamamos a los proceso de procesar las imagenes
    // procesoCalcularHistogramas(calcularHistogramaManual);
    // procesoCalcularHistogramas(calcularHistogramaOpencv);
    // procesoRestarImagenes();
    // procesoRestaImagenesVideo();
    // procesoFiltrosMediaYGausiana();
    // procesoVideoEspacioDeColorHSV();
    // procesoDeteccionDeBordesSobel();
    // procesoDeteccionDeBordesLaplace();
    // procesoDeteccionDeBordesCanny();
    // procesoDeteccionDeBordesVideo();
    // procesoRuidoSalPimienta(false);
    // procesoUmbralizacionGris();
    // procesoUmbralizacionHSV();
    // procesoCortarTriangulo();
    // procesoCortarFuncionSeno();
    // procesoCortarTriangulo2();
    procesoCompletarCirculo();
    // Quedamos en espera de que se presione alguna tecla
    waitKey(0);
    destroyAllWindows();
    return 0;
}


