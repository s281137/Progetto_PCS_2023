#include "empty_class.hpp"

namespace ProjectLibrary
{
  //IMPORTO DA FILE
  bool ImportCell0Ds(TriangularMesh& mesh,string nome_file)
  {
      ifstream file;

      //sostituire il nome file passandolo come stringa

      file.open(nome_file);

      if(file.fail())
          return false;

      list<string> listLines;
      string line;
      while (getline(file, line))
          listLines.push_back(line);
      file.close();

      listLines.pop_front();  //tolgo il primo elemento (riga con id marker ecc)

      mesh.NumberCell0D = listLines.size();

      if (mesh.NumberCell0D == 0)
      {
        cerr << "There is no cell 0D" << endl;
        return false;
      }

      for (const string& line : listLines)
      {
          istringstream converter(line);

          unsigned int marker;
          Point punto;

          converter >>  punto.id >> marker >> punto.x >> punto.y;

          mesh.Cell0D_Id_Coor.push_back(punto);

          if( marker != 0)   //
          {
              if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
                  mesh.Cell0DMarkers.insert({marker, {punto.id}});
              else
                  mesh.Cell0DMarkers[marker].push_back(punto.id);
          }
      }
      file.close();
      return true;
  }

  bool ImportCell1Ds(TriangularMesh& mesh,string nome_file)
  {

    ifstream file;
    file.open(nome_file);

    if(file.fail())
      return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
      listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
      cerr << "There is no cell 1D" << endl;
      return false;
    }

    for (const string& line : listLines)
    {
      istringstream converter(line);

      unsigned int marker;
      Segmento seg;

      converter >>  seg.id >> marker >> seg.id_iniz >> seg.id_fin;

      mesh.Cell1D_Segmenti.push_back(seg);

      if( marker != 0)
      {
        if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
          mesh.Cell1DMarkers.insert({marker, {seg.id}});
        else
          mesh.Cell1DMarkers[marker].push_back(seg.id);
      }
    }

    file.close();
    return true;
  }

  bool ImportCell2Ds(TriangularMesh& mesh,string nome_file)
  {
    ifstream file;
    file.open(nome_file);

    if(file.fail())
      return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
      listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
      cerr << "There is no cell 2D" << endl;
      return false;
    }

    for (const string& line : listLines)
    {
      istringstream converter(line);

      Triangolo tria;

      converter >>  tria.id;
      for(unsigned int i = 0; i < 3; i++)
        converter >> tria.vertices[i];
      for(unsigned int i = 0; i < 3; i++)
        converter >> tria.edges[i];

      mesh.Cell2D_Triangoli.push_back(tria);

    }
    file.close();
    return true;
  }

  double Lunghezza(vector<Point> punti, Segmento segm)
  {
    double distanza=sqrt((punti[segm.id_iniz].x-punti[segm.id_fin].x)*(punti[segm.id_iniz].x-punti[segm.id_fin].x)+(punti[segm.id_iniz].y-punti[segm.id_fin].y)*(punti[segm.id_iniz].y-punti[segm.id_fin].y));
    return distanza;
  }

  double Area(vector<Point> punti, Triangolo triang)
  {
    double area=0.0;
    for(unsigned int i=0;i<3;i++)
    {
        area+=punti[triang.vertices[i%3]].x*punti[triang.vertices[(i+1)%3]].y-punti[triang.vertices[(i+1)%3]].x*punti[triang.vertices[i%3]].y;    
    }
    area=abs(area/2);

    return area;
  }

  void PuntoMedio(vector<Point>& punti,unsigned int& num_punti, Segmento segm)
  {
    Point puntoMedio;
    puntoMedio.x=(punti[segm.id_iniz].x+punti[segm.id_fin].x)/2;
    puntoMedio.y=(punti[segm.id_iniz].y+punti[segm.id_fin].y)/2;
    puntoMedio.id=num_punti;
    punti.push_back(puntoMedio);
    num_punti+=1;
  }

}

