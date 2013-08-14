#ifndef SHAPEPOPULATIONVIEWER_H
#define SHAPEPOPULATIONVIEWER_H

// local
#include "ui_ShapePopulationViewer.h"

// Basics
#include <vtkSmartPointer.h>
#include <sstream>

// PolyData
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataNormals.h>
#include <vtkActor2DCollection.h>


// Visualization
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <QVTKWidget.h>

// Scalars
#include <vtkPointData.h>
#include <vtkFloatArray.h>
//#include <vtkDataArray.h>
//#include <vtkScalarsToColors.h>

// Transfer Function
#include <vtkColorTransferFunction.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarActor.h>

// Window Annotations
#include <vtkCornerAnnotation.h>
#include <vtkTextProperty.h>

// QT
#include <QFileDialog>
#include <QKeyEvent>
#include <QKeySequence>
#include <QDebug>
#include <QGridLayout>



/**
 * ShapePopulationViewer Gui class specification.  This class contains all model data and controller callbacks, if we are going to consider the code within the MVC paradigm.  See
 * ui_ShapePopulationViewer.h for information on the construction of the gui itself.  It is an autogenerated file from the ShapePopulationViewer.ui file, which could also be used as reference.
 *
 * Generally speaking there are two classes of functionality given by the code, viewing options and filesystem interaction.  The filesystem interaction is supported by callbacks which an both read and write meshes to .vtk
 * formatted files.  The viewing option functionality includes the propogation of renderer interaction between QVTKWidgets, the ability to rearrange the QVTKWidgets in a user specified number of columns, and the ability to
 * change the colormap used to view the meshes, ranging over any colormap present in the .vtk file originally.
 *
 * @brief The ShapePopulationViewer class
 * @author Michael Guarino
 */
class ShapePopulationViewer : public QMainWindow, public Ui::ShapePopulationViewer
{
  Q_OBJECT

public:

    ShapePopulationViewer();
  ~ShapePopulationViewer() {} //TO DO : Desallocate pointers

protected:

    /**
    * Number of meshes already displayed
    * @brief numberOfMeshes
    */
    unsigned int numberOfMeshes;
    /**
    * Last directory containing opened files
    * @brief lastDirectory
    */
    QString lastDirectory;
    /**
    * The common colormaps
    * @brief colorMapList
    */
    QStringList commonColorMaps;
    /**
     * vtkcamera shared by the renderWindows when the surfaces are synchronized
     * @brief headcam
     */
    vtkCamera *headcam;
    /**
    * The user selected files
    * @brief meshesList
    */
    QFileInfoList fileList;
   /**
    * vector of vtkPolyData
    * @brief polyDataList
    */
    QVector<vtkPolyData *> *polyDataList;
   /**
    * vector of vtkRenderer
    * @brief rendererList
    */
    QVector<vtkRenderer *> *rendererList;
   /**
    * vector of QVTKWidget
    * @brief widgetList
    */
   QVector<QVTKWidget *> *widgetList;
   /**
    * Vector of vtkRenderWindows selected
    * @brief windowList
    */
   QVector<vtkRenderWindow *> *selectedWindows;


   //DISPLAY
   void updateWidgets();
   void SelectWidget(vtkObject* selectedObject, unsigned long, void*);
   void UnselectWidget(vtkObject*, unsigned long, void* voidEvent);
   void ModifiedHandler();
   void compute_colorMaps_intersection();

   //PLACING WIDGETS
   void printColNumber(int colNumber);
   int getNumberOfColumns();
   int getNumberOfRows(int colNumber);
   void placeWidgetInArea(int colNumber);
   void resizeWidgetInArea();
   void resizeEvent(QResizeEvent* event);

protected slots:
\
   //QUIT
   void slotExit();


   //MENU
   void writeMeshes();
   void openDirectory();
   void openFiles();
   void deleteAll();
   void deleteSelection();
   void flipSelection();

   //VIEW
   void on_radioButton_DISPLAY_all_toggled();  //all
   void on_radioButton_DISPLAY_square_toggled(); //square
   void on_spinBox_DISPLAY_columns_editingFinished();
   void on_slider_DISPLAY_columns_valueChanged();
   void on_slider_DISPLAY_columns_sliderReleased();

   //SYNCHRONIZATION
   void on_radioButton_SYNC_realtime_toggled();
   void on_radioButton_SYNC_delayed_toggled();
   void on_checkBox_SYNC_all_toggled(bool checked);

   //COLORMAP
   void on_comboBox_VISU_colormap_currentIndexChanged();
   void on_toolButton_CENTER_origin_clicked();

   //AXIS
   void viewChange(int x, int y, int z);
   void on_toolButton_VIEW_reset_clicked();
   void on_toolButton_VIEW_P_clicked();
   void on_toolButton_VIEW_A_clicked();
   void on_toolButton_VIEW_L_clicked();
   void on_toolButton_VIEW_R_clicked();
   void on_toolButton_VIEW_S_clicked();
   void on_toolButton_VIEW_I_clicked();

};

#endif
