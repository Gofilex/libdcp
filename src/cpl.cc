#include "cpl.h"

using namespace std;
using namespace libdcp;

CPL::CPL (string file)
	: XMLFile (file, "CompositionPlaylist")
{
	id = string_node ("Id");
	annotation_text = string_node ("AnnotationText");
	issue_date = string_node ("IssueDate");
	creator = string_node ("Creator");
	content_title_text = string_node ("ContentTitleText");
	content_kind = kind_node ("ContentKind");
	content_version = sub_node<ContentVersion> ("ContentVersion");
	ignore_node ("RatingList");
	reels = sub_nodes<Reel> ("ReelList", "Reel");

	done ();
}

ContentVersion::ContentVersion (xmlpp::Node const * node)
	: XMLNode (node)
{
	id = string_node ("Id");
	label_text = string_node ("LabelText");
	done ();
}

Reel::Reel (xmlpp::Node const * node)
	: XMLNode (node)
{
	id = string_node ("Id");
	asset_list = sub_node<CPLAssetList> ("AssetList");

	done ();
}

CPLAssetList::CPLAssetList (xmlpp::Node const * node)
	: XMLNode (node)
{
	main_picture = sub_node<MainPicture> ("MainPicture");
	main_sound = optional_sub_node<MainSound> ("MainSound");

	done ();
}

MainPicture::MainPicture (xmlpp::Node const * node)
	: XMLNode (node)
{
	id = string_node ("Id");
	annotation_text = string_node ("AnnotationText");
	edit_rate = fraction_node ("EditRate");
	intrinsic_duration = int64_node ("IntrinsicDuration");
	entry_point = int64_node ("EntryPoint");
	duration = int64_node ("Duration");
	frame_rate = fraction_node ("FrameRate");
	screen_aspect_ratio = fraction_node ("ScreenAspectRatio");

	done ();
}

MainSound::MainSound (xmlpp::Node const * node)
	: XMLNode (node)
{
	id = string_node ("Id");
	annotation_text = string_node ("AnnotationText");
	edit_rate = fraction_node ("EditRate");
	intrinsic_duration = int64_node ("IntrinsicDuration");
	entry_point = int64_node ("EntryPoint");
	duration = int64_node ("Duration");

	done ();
}