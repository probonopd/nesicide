#include <stdint.h>

#include "cmusics.h"

#include "main.h"

CMusics::CMusics(IProjectTreeViewItem* parent)
{
   // Add node to tree
   InitTreeItem(":/resources/folder_closed.png",parent);
}

CMusics::~CMusics()
{
   // Remove any allocated children
   for ( int i = m_musics.count()-1; i >= 0; i-- )
   {
      delete m_musics.at(i);
   }

   // Initialize this node's attributes
   m_musics.clear();
}

void CMusics::initializeProject()
{
   // Remove any allocated children
   for ( int i = m_musics.count()-1; i >= 0; i-- )
   {
      removeChild(m_musics.at(i));
      delete m_musics.at(i);
   }

   // Initialize this node's attributes
   m_musics.clear();
}

void CMusics::terminateProject()
{
   // Remove any allocated children
   for ( int i = m_musics.count()-1; i >= 0; i-- )
   {
      removeChild(m_musics.at(i));
      delete m_musics.at(i);
   }

   // Initialize this node's attributes
   m_musics.clear();
}

bool CMusics::serialize(QDomDocument& doc, QDomNode& node)
{
   QDomElement musicsElement = addElement( doc, node, "musics" );

   for (int i = 0; i < m_musics.count(); i++)
   {
      if (!m_musics.at(i)->serialize(doc, musicsElement))
      {
         return false;
      }
   }

   return true;
}

bool CMusics::deserialize(QDomDocument& doc, QDomNode& node, QString& errors)
{
   QDomNode childNode = node.firstChild();

   if (!childNode.isNull())
   {
      do
      {
         if (childNode.nodeName() == "music")
         {
            CMusic* pNewMusic = new CMusic(this);
            m_musics.append(pNewMusic);
            appendChild(pNewMusic);

            if (!pNewMusic->deserialize(doc,childNode,errors))
            {
               return false;
            }
         }
         else
         {
            return false;
         }
      }
      while (!(childNode = childNode.nextSibling()).isNull());
   }

   return true;
}

QString CMusics::caption() const
{
   return QString("Musics");
}

void CMusics::contextMenuEvent(QContextMenuEvent* event, QTreeView* parent)
{
}