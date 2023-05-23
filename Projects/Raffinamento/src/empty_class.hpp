#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "map"

using namespace std;
using namespace Eigen;

namespace ProjectLibrary
{
   constexpr double max_tolerance(const double& x, const double& y)
   {
      return x > y ? x : y;
   }

   struct Point
   {
      double x;
      double y;
      unsigned int id;

      static constexpr double geometricTol = 1.0e-12;
      static constexpr double geometricTol_Squared = max_tolerance(Point::geometricTol * Point::geometricTol,numeric_limits<double>::epsilon());

      Point(const double& x=0.0,
            const double& y=0.0,
            const unsigned int& id=0):
        x(x), y(y), id(id)
        {
        }
    };

   struct Segmento
   {
       unsigned int id_iniz;
       unsigned int id_fin;
       unsigned int id;
       double lunghezza;


       Segmento(const unsigned int& id_iniz=0,
                const unsigned int& id_fin=0,
                const unsigned int& id=0,
                const double& lunghezza=0.0):
         id_iniz(id_iniz), id_fin(id_fin), id(id), lunghezza(lunghezza)
         {
         }
    };

   struct Triangolo
   {
       Vector3i edges;
       Vector3i vertices;
       unsigned int id;
       double area;


       Triangolo(const Vector3i& edges=Vector3i::Zero(),
                 const Vector3i& vertices=Vector3i::Zero(),
                 const unsigned int& id=0,
                 double area=0.0):
         edges(edges), vertices(vertices), id(id), area(area)
         {
         }
    };

   //OPERATORI PER PUNTI --> ID

   inline double normSquared(const double& x, const double& y)
   {
      return x * x + y * y;
   }

   inline bool operator>(const Point& p1, const Point& p2)
   {
      return (p1.id > p2.id);
   }

   inline bool operator<=(const Point& p1, const Point& p2)
   {
      return !(p1 > p2);
   }

   inline bool operator==(const Point& p1, const Point& p2)
   {
     return (normSquared(p1.x - p2.x, p1.y - p2.y) <=
             Point::geometricTol * Point::geometricTol *
             max(normSquared(p1.x, p1.y), normSquared(p2.x, p2.y)));
   }

   inline bool operator!=(const Point& p1, const Point& p2)
   {
      return !(p1 == p2);
   }

   inline ostream& operator<<(ostream& os, const Point& p2)
   {
      os << p2.id;
      return os;
   }

   //OPERATORI PER TRIANGOLI --> AREE

   /*inline bool operator==(const Triangolo& t1, const Triangolo& t2)
   {
       return (abs(t1.area - t2.area) <= Point::geometricTol * Point::geometricTol * max(t1.area, t2.area));
   }*/

   inline bool operator>(const Triangolo& t1, const Triangolo& t2)
   {
      return (t1.area < t2.area + Point::geometricTol * Point::geometricTol * max(t1.area, t2.area));
   }//Chiamo l'operatore > ma in realtà controlla se è minore

   inline bool operator<=(const Triangolo& t1, const Triangolo& t2)
   {
      return !(t1 > t2);
   }

   //OPERATORI PER SEGMENTI --> LATO

   inline bool operator>(const Segmento& t1, const Segmento& t2)
   {
      return (t1.lunghezza < t2.lunghezza + Point::geometricTol * max(t1.lunghezza, t2.lunghezza));
   }//Chiamo l'operatore > ma in realtà controlla se è minore

   inline bool operator<=(const Segmento& t1, const Segmento& t2)
   {
      return !(t1 > t2);
   }

   struct TriangularMesh
   {
       unsigned int NumberCell0D = 0; ///< number of Cell0D
       std::vector<Point> Cell0D_Id_Coor = {};
       std::map<unsigned int, list<unsigned int>> Cell0DMarkers = {}; ///< Cell0D markers, size 1 x NumberCell0D (marker)

       unsigned int NumberCell1D = 0; ///< number of Cell1D
       std::vector<Segmento> Cell1D_Segmenti = {};
       std::map<unsigned int, list<unsigned int>> Cell1DMarkers = {}; ///< Cell1D propertoes, size 1 x NumberCell1D (marker)

       unsigned int NumberCell2D = 0; ///< number of Cell2D
       std::vector<Triangolo> Cell2D_Triangoli = {};

   };

   bool ImportCell0Ds(TriangularMesh& mesh,string nome_file);  //vertici

   bool ImportCell1Ds(TriangularMesh& mesh,string nome_file);  //segmenti

   bool ImportCell2Ds(TriangularMesh& mesh,string nome_file);  //triangoli

   double Lunghezza(vector<Point> punti, Segmento segm);

   double Area(vector<Point> punti, Triangolo triang);

   void PuntoMedio(vector<Point>& punti,unsigned int& num_punti, Segmento segm);

   template<typename T>
   void Merge(vector<T>& v, const unsigned int& sx, const unsigned int& cx, const unsigned int& dx)
   {
       unsigned int i=sx;
       unsigned int j=cx+1;
       vector<T> supp;
       while((i<=cx)&&(j<=dx))
       {
           if(v[i]<=v[j])
           {
               supp.push_back(v[i]);
               i+=1;
           }else
           {
               supp.push_back(v[j]);
               j+=1;
           }
       }
       for(unsigned int s =i; s<=cx ; s++)
       {
           supp.push_back(v[s]);
       }
       for(unsigned int t = j; t<=dx ; t++)
       {
           supp.push_back(v[t]);
       }
       for(unsigned int k = sx; k<=dx ; k++)
       {
           v[k]=supp[k-sx];
       }
    }

   template<typename T>
   void MergeSort(vector<T>& v, const unsigned int& sx, const unsigned int& dx)
   {
       int cx;
       if(sx<dx)
       {
           cx=(sx+dx)/2;
           MergeSort(v,sx,cx);
           MergeSort(v,cx+1,dx);
           Merge(v,sx,cx,dx);
       }
     }


}

#endif // __EMPTY_H
