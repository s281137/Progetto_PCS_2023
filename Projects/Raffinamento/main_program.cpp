#include "empty_class.hpp"

int main()
{
  /*ProjectLibrary::Empty empty;

  empty.Show();*/

  // IMPORTAZIONE DEI DATI
  ProjectLibrary::TriangularMesh mesh;
  string nome_file="C:/Users/franc/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell0Ds.csv";
  if(!ImportCell0Ds(mesh,nome_file))
  {
    return -1;
  }
  nome_file="C:/Users/franc/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell1Ds.csv";
  if(!ImportCell1Ds(mesh,nome_file))
  {
    return -1;
  }
  nome_file="C:/Users/franc/Desktop/PCS2023_Exercises/Projects/Raffinamento/Dataset/Test1/Cell2Ds.csv";
  if(!ImportCell2Ds(mesh,nome_file))
  {
    return -1;
  }

  //ORDINO I PUNTI IN BASE ALL'ID (NEL NOSTRO CASO NON SERVE MA LO FACCIAMO PER GENERALITà)
  //ProjectLibrary::MergeSort(mesh.Cell0D_Id_Coor, 0, mesh.NumberCell0D-1);

  //CALCOLO LA LUNGHEZZA DEI SEGMENTI
  for(unsigned int i=0;i<mesh.NumberCell1D;i++)
      mesh.Cell1D_Segmenti[i].lunghezza=Lunghezza(mesh.Cell0D_Id_Coor,mesh.Cell1D_Segmenti[i]);

  //CALCOLO LE AREE DEI TRIANGOLI
  for(unsigned int i=0;i<mesh.NumberCell2D;i++)
      mesh.Cell2D_Triangoli[i].area=Area(mesh.Cell0D_Id_Coor,mesh.Cell2D_Triangoli[i]);

  //ORDINARE I TRIANGOLI IN BASE ALLE AREE
  ProjectLibrary::MergeSort(mesh.Cell2D_Triangoli, 0, mesh.NumberCell2D-1);

  //DEFINISCO E FISSO TETA= VALORE SOGLIA AREA OLTRE IL QUALE DIVIDO IL TRIANGOLO
  double teta=0.0;
  for(unsigned int i=0;i<mesh.NumberCell2D;i++)
      teta+=mesh.Cell2D_Triangoli[i].area;
  teta=teta/mesh.NumberCell2D;  //Scelgo teta come la media delle aree
  int id_lato_max=0;

  //DIVIDO LE AREE FINO A QUANDO QUELLA MAGGIORE DIVENTA MINORE DI TETA
  //while(mesh.Cell2D_Triangoli[0].area>teta)
  //{
    //CERCO IL LATO PIù LUNGO
      /*
      if(mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[0]].lunghezza<mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[1]].lunghezza)
      {
          if(mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[1]].lunghezza<mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[2]].lunghezza)
          {
              id_lato_max=mesh.Cell2D_Triangoli[0].edges[2];
          }else
          {
              id_lato_max=mesh.Cell2D_Triangoli[0].edges[1];
          }
      }else
      {
          if(mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[0]].lunghezza<mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[2]].lunghezza)
          {
              id_lato_max=mesh.Cell2D_Triangoli[0].edges[2];
          }else
          {
              id_lato_max=mesh.Cell2D_Triangoli[0].edges[0];
          }

      }*/

      vector<ProjectLibrary::Segmento> supp_lato_lungo={};
      supp_lato_lungo.push_back(mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[0]]);
      supp_lato_lungo.push_back(mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[1]]);
      supp_lato_lungo.push_back(mesh.Cell1D_Segmenti[mesh.Cell2D_Triangoli[0].edges[2]]);
      ProjectLibrary::MergeSort(supp_lato_lungo, 0, 2);
      id_lato_max=supp_lato_lungo[0].id;

      //CALCOLO PUNTO MEDIO LATO PIù LUNGO
      PuntoMedio(mesh.Cell0D_Id_Coor,mesh.NumberCell0D, mesh.Cell1D_Segmenti[id_lato_max]);

  //}



  //--------------------CONTROLLI-----------------------------
  /*for(unsigned int i=0;i<mesh.NumberCell0D;i++)
      cout<<"ID: "<<mesh.Cell0D_Id_Coor[i].id<<" X: "<<mesh.Cell0D_Id_Coor[i].x<<" Y: "<<mesh.Cell0D_Id_Coor[i].y<<endl;
  cout<<endl;*/

  /*for(unsigned int i=0;i<mesh.NumberCell1D;i++)
        cout<<"ID: "<<mesh.Cell1D_Segmenti[i].id<<" VERTICI: "<<mesh.Cell1D_Segmenti[i].id_iniz<<" "<<mesh.Cell1D_Segmenti[i].id_fin<<" LUNGHEZZA: "<<mesh.Cell1D_Segmenti[i].lunghezza<<endl;
  cout<<endl;*/

  /*for(unsigned int i=0;i<mesh.NumberCell2D;i++)
          cout<<"ID: "<<mesh.Cell2D_Triangoli[i].id<<" VERTICI: "<<mesh.Cell2D_Triangoli[i].vertices[0]<<"-"<<mesh.Cell2D_Triangoli[i].vertices[1]<<"-"<<mesh.Cell2D_Triangoli[i].vertices[2]<<" LATI: "<<mesh.Cell2D_Triangoli[i].edges[0]<<"-"<<mesh.Cell2D_Triangoli[i].edges[1]<<"-"<<mesh.Cell2D_Triangoli[i].edges[2]<<" AREA: "<<mesh.Cell2D_Triangoli[i].area<<endl;
  cout<<endl;*/

  return 0;
}
