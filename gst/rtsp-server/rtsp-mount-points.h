/* GStreamer
 * Copyright (C) 2008 Wim Taymans <wim.taymans at gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <gst/gst.h>

#include <gst/rtsp/gstrtspurl.h>

#include "rtsp-media-factory.h"

#ifndef __GST_RTSP_MOUNT_POINTS_H__
#define __GST_RTSP_MOUNT_POINTS_H__

G_BEGIN_DECLS

#define GST_TYPE_RTSP_MOUNT_POINTS              (gst_rtsp_mount_points_get_type ())
#define GST_IS_RTSP_MOUNT_POINTS(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_RTSP_MOUNT_POINTS))
#define GST_IS_RTSP_MOUNT_POINTS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_RTSP_MOUNT_POINTS))
#define GST_RTSP_MOUNT_POINTS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_RTSP_MOUNT_POINTS, GstRTSPMountPointsClass))
#define GST_RTSP_MOUNT_POINTS(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_RTSP_MOUNT_POINTS, GstRTSPMountPoints))
#define GST_RTSP_MOUNT_POINTS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_RTSP_MOUNT_POINTS, GstRTSPMountPointsClass))
#define GST_RTSP_MOUNT_POINTS_CAST(obj)         ((GstRTSPMountPoints*)(obj))
#define GST_RTSP_MOUNT_POINTS_CLASS_CAST(klass) ((GstRTSPMountPointsClass*)(klass))

typedef struct _GstRTSPMountPoints GstRTSPMountPoints;
typedef struct _GstRTSPMountPointsClass GstRTSPMountPointsClass;

/**
 * GstRTSPMountPoints:
 * @parent: parent GObject
 * @mounts: the mountpoints to mediafactory mapping
 *
 * Creates a #GstRTSPMediaFactory object for a given url.
 */
struct _GstRTSPMountPoints {
  GObject       parent;

  GMutex        lock;
  GHashTable   *mounts;
};

/**
 * GstRTSPMountPointsClass:
 * @parent_class: parent GObject class
 * @find_factory: Create or return a previously cached #GstRTSPMediaFactory object
 *        for the given url. the default implementation will use the factory
 *        added with gst_rtsp_mount_points_add_factory().
 *
 * The class for the media mounts object.
 */
struct _GstRTSPMountPointsClass {
  GObjectClass  parent_class;

  GstRTSPMediaFactory * (*find_factory)  (GstRTSPMountPoints *mounts, const GstRTSPUrl *url);
};

GType                 gst_rtsp_mount_points_get_type       (void);

/* creating a mount points */
GstRTSPMountPoints *  gst_rtsp_mount_points_new            (void);

/* finding a media factory */
GstRTSPMediaFactory * gst_rtsp_mount_points_find_factory   (GstRTSPMountPoints *mounts, const GstRTSPUrl *url);

/* managing media to a mount point */
void                  gst_rtsp_mount_points_add_factory    (GstRTSPMountPoints *mounts, const gchar *path,
                                                            GstRTSPMediaFactory *factory);
void                  gst_rtsp_mount_points_remove_factory (GstRTSPMountPoints *mounts, const gchar *path);

G_END_DECLS

#endif /* __GST_RTSP_MOUNT_POINTS_H__ */