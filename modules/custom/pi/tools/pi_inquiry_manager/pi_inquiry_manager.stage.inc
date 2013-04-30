<?php

function pi_inquiry_manager_stage_selector() {
	$access_data = pi_inquiry_groupings_get_access_data();
	if ($access_data->get_inquiry_node()) {
		if ($access_data->user_is_inquiry_owner()) {
			$output = drupal_get_form('pi_inquiry_manager_stage_selector_form');
		} else {
			$output = pi_inquiry_manager_stage_selector_view();
		}
		return $output;
	}
}

function pi_inquiry_manager_stage_selector_view() {
	$access_data = pi_inquiry_groupings_get_access_data();
	$all_stages_structure = $access_data->get_all_stages_structure();
	
	_pi_inquiry_manager_stage_selector_load_javascript($all_stages_structure['values'], $access_data->get_current_stage()->nid);
		
	$output = theme('nquire_structure_widget_stage_view', 'stageselector', json_encode($all_stages_structure['structure']));
	
	return $output;
}

function pi_inquiry_manager_stage_selector_form(&$form_state) {
	$form = array();

	$access_data = pi_inquiry_groupings_get_access_data();
	$all_stages_structure = $access_data->get_all_stages_structure();
	$value = $access_data->get_current_stage()->nid;
	nquire_structure_widget_stage_selector_create_form_item($form, 'stageselector', json_encode($all_stages_structure['structure']), $value);

	_pi_inquiry_manager_stage_selector_load_javascript($all_stages_structure['values']);

	nquire_commons_create_form_save_cancel_buttons($form, 'pi_inquiry_manager_stage_selector_form_submit', 'inquiry/' . $access_data->get_inquiry_nid() . '/share');

	return $form;
}

function _pi_inquiry_manager_stage_selector_load_javascript($stage_phase_values, $highlight_column = NULL) {
	$stage_phase_str = json_encode($stage_phase_values);
	$module = "{"
					. "  init: function() {"
					. "    this.stages = $stage_phase_str;"
					. "    this.highlightColumn = '$highlight_column';"
					. "  }"
					. "}";
	nquire_commons_inject_inline_javascript_module('InquiryStagePhaseValues', $module);
}

function pi_inquiry_manager_stage_selector_form_submit($form, $form_state) {
	$access_data = pi_inquiry_groupings_get_access_data();
	if ($access_data->user_is_inquiry_owner()) {
		$value = $form_state['values']['stageselector'];
		$query = "INSERT INTO pi_stage_current (inquiry_id, stage_id) VALUES (%d, %d) ON DUPLICATE KEY UPDATE stage_id=%d";
		db_query($query, $access_data->get_inquiry_nid(), $value, $value);
	}
}