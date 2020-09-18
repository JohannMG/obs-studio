#pragma once

#include <string>
#include <math.h>
#include <QString>

namespace StreamWizard {
enum class VideoType {
	live, // Streaming
	vod,  // Video On Demand, recording uploads
};

enum class StreamProtocol {
	rmpts,
};

enum class VideoCodec {
	h264,
};

enum class AudioCodec {
	aac,
};

enum class StreamRateControlMode {
	cbr,
	abr,
	vbr,
	crf,
};

/* There are two launch contexts for starting the wizard
	- PreStream: the wizard is triggered between pressing Start Streaming and a
	stream. So the user wizard should indicate when the encoder is ready to stream
	but also allow the user to abort. 

	- Settings: User start config workflow from the settings page or toolbar. 
		In this case, the wizard should not end with the stream starting but may end
		wutg saving the settings if given signal 
*/
enum class LaunchContext {
	PreStream,
	Settings,
};

/* 
	To make the wizard expandable we can have multiple destinations. 
	In the case Facebook, it will use Facebook's no-auth encoder API.
*/
enum class Destination {
	Facebook,
};

// Data to send to encoder config API
struct EncoderSettingsRequest {
	//// Stream
	StreamProtocol protocol; // Expandable but only supports RTMPS for now
	VideoType videoType;     // LIVE or VOD (but always live for OBS)
	char *serverUrl;
	char *serviceName;

	///// Video Settings
	int videoWidth;
	int videoHeight;
	double framerate; // in frames per second
	int videoBitrate; // in kbps e.g., 4000kbps
	VideoCodec videoCodec;

	///// Audio Settings
	int audioChannels;
	int audioSamplerate; // in Hz, e.g., 48000Hz
	int audioBitrate;    // in kbps e.g., 128kbps
	AudioCodec audioCodec;
};

// To be recieved from encoder config API to suggest new ideal
struct EncoderSettingsResponse {
	// For response
	int videoWidth;
	int videoHeight;
	double framerate; // in FPS
	int videoBitrate; // in kbps
	int audioChannels;
	int audioSamplerate; // in Hz, e.g., 48000Hz
	int audioBitrate;    // in kbps e.g., 128kbps
	StreamProtocol protocol;
	VideoCodec videoCodec;
	AudioCodec audioCodec;

	/* Video Codec Settings */
	QString h264Profile; // "high"
	float h264Level;     // 1 ... 6

	/* Group of Pictures (gop) settings  */
	int gopSizeInFrames;
	int gopSizeInSeconds(void)
	{
		// Uses ceil to account for drop-frame: we round up 23.96 -> 24
		return (int)(gopSizeInFrames / ceil(framerate));
	};
	// Open-GOP is an encoding technique which increases efficiency but often is
	// not compatible with streaming
	bool gopClosed;
	int gopBFrames; // per group-of-pictures
	int gopRefFrames; // Controls the size of the DPB (Decoded Picture Buffer).

	bool videoProgressiveScan;
	StreamRateControlMode streamRateControlMode;
	int streamBufferSize; // in Kb
};

}
