/**
 * Copyright L. Spiro 2023
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: Uses OpenAL to handle all for our audio needs.  As an emulator, we just need a single device, context, and source.
 *	This class owns and manages the objects and provides the interface we need to generate audio.
 */

#include "LSNAudio.h"
#include "../Utilities/LSNUtilities.h"

namespace lsn {

	// == Members.
	/** The audio interface object. */
	CAudioOpenAl CAudio::m_aoaOpenAlAudio;

	/** The audio thread. */
	std::unique_ptr<std::thread> CAudio::m_ptAudioThread;

	/** Boolean to stop the audio thread. */
	std::atomic<bool> CAudio::m_bRunThread = true;

	/** The signal that the thread has finished. */
	CEvent CAudio::m_eThreadClosed;

	/** The sample box for band-passed output. */
	CSampleBox CAudio::m_sbSampleBox;


	// == Functions.
	/**
	 * Initializes audio.
	 * 
	 * \return Returns true if initialization was successful.
	 **/
	bool CAudio::InitializeAudio() {
		m_sbSampleBox.SetFeatureSet( CUtilities::IsAvx512FSupported(), CUtilities::IsAvxSupported(), CUtilities::IsSse4Supported() );

		if ( !m_aoaOpenAlAudio.InitializeAudio() ) { return false; }

		if ( !StartThread() ) { return false; }
		return true;
	}

	/**
	 * Shuts down the audio.
	 * 
	 * \return Returns true if shutdown was successful.
	 **/
	bool CAudio::ShutdownAudio() {
		StopThread();
		
		return m_aoaOpenAlAudio.ShutdownAudio();
	}

	/**
	 * Called when emulation begins.  Resets the ring buffer of buckets.
	 **/
	void CAudio::BeginEmulation() {
		StopThread();

		m_aoaOpenAlAudio.BeginEmulation();

		StartThread();
	}

	/**
	 * Adds a sample to all buckets that need it.
	 *
	 * \param _fSample The audio sample to be added.
	 **/
	void CAudio::AddSample( float _fSample ) {
		m_sbSampleBox.AddSample( _fSample );
		std::vector<float> & vOut = m_sbSampleBox.Output();
		for ( size_t I = 0; I < vOut.size(); ++I ) {
			m_aoaOpenAlAudio.AddSample( vOut[I] );
		}
		vOut.clear();
	}

	/**
	 * Starts the audio thread.
	 * 
	 * \return Returns true if the audio thread is started.
	 **/
	bool CAudio::StartThread() {
		return true;	// No audio thread yet.
		/*StopThread();
		m_bRunThread = true;
		m_ptAudioThread = std::make_unique<std::thread>( AudioThread, nullptr );
		return m_ptAudioThread.get() != nullptr;*/
	}

	/**
	 * Stops the audio thread.
	 **/
	void CAudio::StopThread() {
		if ( nullptr == m_ptAudioThread.get() ) { return; }
		m_bRunThread = false;
		m_eThreadClosed.WaitForSignal();
		m_ptAudioThread->join();
		m_ptAudioThread.reset();
	}

	/**
	 * The audio thread.
	 *
	 * \param _pvParm Unused.
	 */
	void CAudio::AudioThread( void * /*_pvParm*/ ) {
		while ( m_bRunThread ) {
		}
		m_eThreadClosed.Signal();
	}

}	// namespace lsn
