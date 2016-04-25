#include <QApplication>
#include <qgsproject.h>
#include <qgsmapcanvas.h>
#include <qgsmaplayerregistry.h>
#include <qgsmaprenderersequentialjob.h>
#include <qgsapplication.h>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  // directory where data providers are located
  QgsApplication::setPrefixPath("/usr/local", true);
  QgsApplication::initQgis();

  // load layers from a project
  QgsProject::instance()->setFileName("/home/hme/Bureau/test_vlayer/test1.qgs");
  QgsProject::instance()->read();

  // setup a mapsettings
  QgsMapSettings mapSettings;
  mapSettings.setFlag( QgsMapSettings::Antialiasing );
  mapSettings.setOutputSize( QSize( 800, 600 ) );

  QStringList layers;
  Q_FOREACH( QgsMapLayer* l, QgsMapLayerRegistry::instance()->mapLayers().values() )
  {
    layers << l->id();
    mapSettings.setExtent( l->extent() );
  }
  mapSettings.setLayers( layers );

  // call a renderer
  QgsMapRendererSequentialJob job( mapSettings );
  // TODO: try QgsMapRendererParallelJob
  job.start();
  job.waitForFinished();

  // save the rendered image
  job.renderedImage().save( "rendered.png" );

  QgsApplication::exitQgis();

  return 0;
}
