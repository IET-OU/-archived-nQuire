<?php

// Include the definition of zen_settings() and zen_theme_get_default_settings().
include_once './' . drupal_get_path('theme', 'zen') . '/theme-settings.php';

/**
 * Implementation of THEMEHOOK_settings() function.
 *
 * @param $saved_settings
 *   An array of saved settings for this theme.
 * @return
 *   A form array.
 */
function nquire_laf_settings($saved_settings) {

	// Get the default values from the .info file.
	$defaults = zen_theme_get_default_settings('nquire_laf');

	// Merge the saved variables and their default values.
	$settings = array_merge($defaults, $saved_settings);

	/*
	 * Create the form using Forms API: http://api.drupal.org/api/6
	 */
	$form = array();
	$form['nquire_laf_color_scheme'] = array(
			'#type' => 'select',
			'#title' => t('Color scheme'),
			'#default_value' => $settings['nquire_laf_color_scheme'],
			'#description' => t("Select the color scheme."),
			'#options' => array(
					'original' => t('Original nQuire'),
					'osl' => t('OSL'),
					'nt' => t('Nominet Trust'),
			),
			'#weight' => -1000,
	);

	// Add the base theme's settings.
//  $form += zen_settings($saved_settings, $defaults);
	// Remove some of the base theme's settings.
//	unset($form['themedev']['zen_layout']); // We don't need to select the base stylesheet.
	// Return the form
	return $form;
}
