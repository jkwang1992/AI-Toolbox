#ifndef AI_TOOLBOX_MDP_PGA_APP_POLICY_HEADER_FILE
#define AI_TOOLBOX_MDP_PGA_APP_POLICY_HEADER_FILE

#include <vector>

#include <AIToolbox/MDP/Policies/QPolicyInterface.hpp>
#include <AIToolbox/MDP/Policies/PolicyWrapper.hpp>
#include <AIToolbox/MDP/Policies/EpsilonPolicy.hpp>

namespace AIToolbox::MDP {
    /**
     * @brief This class models the PGA-APP learning algorithm.
     */
    class PGAAPPPolicy : public QPolicyInterface {
        public:
            /**
             * @brief Basic constructor.
             *
             * See the setter functions to see what the parameters do.
             *
             * @param q The QFunction from which to extract policy updates.
             * @param lRate The learning rate which gradually changes the policy.
             * @param predictionLength How much further to predict opponent changes.
             */
            PGAAPPPolicy(const QFunction & q, double lRate = 0.001, double predictionLength = 3.0);

            /**
             * @brief This function updates the policy based on changes in the QFunction.
             *
             * This function should be called between agent's actions,
             * using the agent's current state.
             *
             * @param s The state that needs to be updated.
             */
            void stepUpdateP(size_t s);

            /**
             * @brief This function chooses an action for state s, following the policy distribution.
             *
             * Note that to improve learning it may be useful to wrap this policy into an EpsilonPolicy
             * in order to provide some exploration.
             *
             * @param s The sampled state of the policy.
             *
             * @return The chosen action.
             */
            virtual size_t sampleAction(const size_t & s) const override;

            /**
             * @brief This function returns the probability of taking the specified action in the specified state.
             *
             * @param s The selected state.
             * @param a The selected action.
             *
             * @return The probability of taking the selected action in the specified state.
             */
            virtual double getActionProbability(const size_t & s, const size_t & a) const override;

            /**
             * @brief This function returns a matrix containing all probabilities of the policy.
             *
             * Ideally this function can be called only when there is a
             * repeated need to access the same policy values in an
             * efficient manner.
             */
            virtual Matrix2D getPolicy() const override;

            /**
             * @brief This function sets the new learning rate.
             *
             * Note: The learning rate must be >= 0.0.
             *
             * @param lRate The new learning rate.
             */
            void setLearningRate(double lRate);

            /**
             * @brief This function returns the current learning rate.
             *
             * @return The current learning rate.
             */
            double getLearningRate() const;

            /**
             * @brief This function sets the new prediction length.
             *
             * Note: The prediction length must be >= 0.0.
             *
             * @param pLength The new learning rate.
             */
            void setPredictionLength(double pLength);

            /**
             * @brief This function returns the current prediction length.
             *
             * @return The current prediction length.
             */
            double getPredictionLength() const;

        private:
            double lRate_, predictionLength_;
            PolicyWrapper::PolicyTable policyTable_;
            PolicyWrapper policy_;
    };
}

#endif
